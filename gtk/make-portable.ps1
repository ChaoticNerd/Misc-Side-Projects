# ================================================
#  PORTABLE PACKAGE BUILDER FOR GTKmm 4 (MSYS2)
#  Uses ntldd to auto-detect DLL dependencies
# ================================================

# ---- CONFIG ----
$MsysRoot    = "C:\msys64"
$SrcBin      = Join-Path $MsysRoot "mingw64\bin"
$SrcShare    = Join-Path $MsysRoot "mingw64\share"
$SrcLib      = Join-Path $MsysRoot "mingw64\lib"

# Path to ntldd from MinGW64 environment
$NtlddExe    = Join-Path $SrcBin "ntldd.exe"

# Folder where this script lives = project root
$ProjectRoot = Split-Path -Parent $MyInvocation.MyCommand.Path

# Output folder: dist\MyGtkApp
$DistRoot  = Join-Path $ProjectRoot "dist"
$OutputDir = Join-Path $DistRoot "MyGtkApp"

$AppExe    = Join-Path $ProjectRoot "build\app.exe"

Write-Host "ProjectRoot: $ProjectRoot"
Write-Host "OutputDir:   $OutputDir"
Write-Host ""

# ---- Ensure exe exists ----
if (!(Test-Path $AppExe)) {
    Write-Error "ERROR: Cannot find app.exe at $AppExe. Build first."
    exit 1
}

# ---- Ensure ntldd exists ----
if (!(Test-Path $NtlddExe)) {
    Write-Error "ERROR: ntldd.exe not found at $NtlddExe."
    Write-Host "Install it from an MSYS2 MinGW64 shell with:"
    Write-Host "  pacman -S mingw-w64-x86_64-ntldd-git"
    exit 1
}

# ---- Rebuild output folder ----
if (Test-Path $OutputDir) {
    Write-Host "Cleaning existing output dir..."
    Remove-Item -Recurse -Force $OutputDir
}
New-Item -ItemType Directory -Path $OutputDir | Out-Null

# ---- Copy executable ----
Write-Host "Copying app.exe..."
Copy-Item $AppExe (Join-Path $OutputDir "app.exe") -Force

# ====================================================
#  COPY USER DATA (data/, assets/, style.css)
# ====================================================

# data -> OutputDir\data
$DataSrc = Join-Path $ProjectRoot "data"
if (Test-Path $DataSrc) {
    Write-Host "Copying data/..."
    Copy-Item $DataSrc (Join-Path $OutputDir "data") -Recurse -Force
} else {
    Write-Host "No data/ directory found; skipping."
}

# assets -> OutputDir\assets
$AssetsSrc = Join-Path $ProjectRoot "assets"
if (Test-Path $AssetsSrc) {
    Write-Host "Copying assets/..."
    Copy-Item $AssetsSrc (Join-Path $OutputDir "assets") -Recurse -Force
} else {
    Write-Host "No assets/ directory found; skipping."
}

# style.css -> OutputDir\style.css
$CssSrc = Join-Path $ProjectRoot "style.css"
if (Test-Path $CssSrc) {
    Write-Host "Copying style.css..."
    Copy-Item $CssSrc (Join-Path $OutputDir "style.css") -Force
} else {
    Write-Host "No style.css found; skipping."
}

# ====================================================
#  Helper: get DLL dependencies via ntldd
# ====================================================

function Get-MingwDllDeps {
    param (
        [Parameter(Mandatory=$true)][string]$BinaryPath
    )

    if (!(Test-Path $BinaryPath)) {
        Write-Warning "  Dependency scan skipped; binary not found: $BinaryPath"
        return @()
    }

    Write-Host "  Running ntldd on: $BinaryPath"
    $output = & $NtlddExe -R "$BinaryPath"

    $dllPaths = @()

    foreach ($line in $output) {
        # Example line formats:
        #   C:\msys64\mingw64\bin\libgtk-4-1.dll => C:\msys64\mingw64\bin\libgtk-4-1.dll (0x...)
        #   libxml2-2.dll => not found
        #   C:\Windows\System32\KERNEL32.DLL => ...
        if ($line -match '=>\s+not found') {
            # e.g. "libxml2-2.dll => not found"
            $missing = $line.Split(' ')[0]
            Write-Warning "    MISSING dependency reported by ntldd: $missing"
            continue
        }

        # Try to capture a full path after "=>"
        if ($line -match '=>\s+([A-Z]:[\\\/][^ ]+)\s*\(') {
            $path = $Matches[1]
            # Only keep DLLs from mingw64\bin (skip system DLLs)
            if ($path -like "$SrcBin\*") {
                $dllPaths += $path
            }
            continue
        }

        # Some lines may be just "C:\msys64\mingw64\bin\libstdc++-6.dll (0x...)"
        if ($line -match '^([A-Z]:[\\\/][^ ]+)\s*\(') {
            $path = $Matches[1]
            if ($path -like "$SrcBin\*") {
                $dllPaths += $path
            }
            continue
        }
    }

    return $dllPaths
}

# ====================================================
#  AUTO-COLLECT DLLs for app.exe and SVG loader
# ====================================================

Write-Host ""
Write-Host "Collecting DLL dependencies via ntldd..."

$dllPaths = @()

# 1) Dependencies of the main exe
$dllPaths += Get-MingwDllDeps -BinaryPath $AppExe

# 2) Dependencies of the SVG pixbuf loader (for Adwaita symbolic icons)
$SvgLoader = Join-Path $SrcLib "gdk-pixbuf-2.0\2.10.0\loaders\pixbufloader_svg.dll"
if (Test-Path $SvgLoader) {
    $dllPaths += Get-MingwDllDeps -BinaryPath $SvgLoader
} else {
    Write-Warning "  SVG loader not found at $SvgLoader"
}

# Deduplicate
$dllPaths = $dllPaths | Sort-Object -Unique

Write-Host ""
Write-Host "Copying DLLs..."
foreach ($src in $dllPaths) {
    $name = Split-Path $src -Leaf
    $dst  = Join-Path $OutputDir $name

    if (Test-Path $src) {
        Copy-Item $src $dst -Force
        Write-Host "  Copied $name"
    } else {
        Write-Warning "  ntldd reported but file missing: $src"
    }
}

# ====================================================
#  COPY GLIB (including schemas)  -> share\glib-2.0
# ====================================================

$GlibSrc = Join-Path $SrcShare "glib-2.0"
$GlibDstParent = Join-Path $OutputDir "share"

Write-Host ""
Write-Host "Copying GLib share (including schemas)..."

if (Test-Path $GlibSrc) {
    # This creates: dist\MyGtkApp\share\glib-2.0\...
    Copy-Item $GlibSrc $GlibDstParent -Recurse -Force
} else {
    Write-Warning "GLib share directory not found at $GlibSrc"
}


# ====================================================
#  COPY GDK-PIXBUF LOADERS  (PNG/JPEG/SVG/TIFF support)
# ====================================================

$PixbufSrc = Join-Path $SrcLib "gdk-pixbuf-2.0"
$PixbufDst = Join-Path $OutputDir "lib\gdk-pixbuf-2.0"

Write-Host ""
Write-Host "Copying GDK-Pixbuf loaders..."
if (Test-Path $PixbufSrc) {
    Copy-Item $PixbufSrc $PixbufDst -Recurse -Force
} else {
    Write-Warning "GDK-pixbuf loader directory not found at $PixbufSrc"
}

# ====================================================
#  COPY GTK RESOURCES  (Adwaita theme, gtk.gresource)
# ====================================================

$GtkShareSrc = Join-Path $SrcShare "gtk-4.0"
$GtkShareDst = Join-Path $OutputDir "share\gtk-4.0"

Write-Host ""
Write-Host "Copying GTK shared data..."
if (Test-Path $GtkShareSrc) {
    Copy-Item $GtkShareSrc $GtkShareDst -Recurse -Force
} else {
    Write-Warning "GTK shared data directory not found at $GtkShareSrc"
}

# ====================================================
#  COPY ICON THEME (Adwaita only)
# ====================================================

$IconsRootSrc = Join-Path $SrcShare "icons"
$IconsRootDst = Join-Path $OutputDir "share\icons"

Write-Host ""
Write-Host "Copying icon theme: Adwaita..."

$AdwaitaSrc = Join-Path $IconsRootSrc "Adwaita"
$AdwaitaDst = Join-Path $IconsRootDst "Adwaita"

if (Test-Path $AdwaitaSrc) {
    try {
        Copy-Item $AdwaitaSrc $AdwaitaDst -Recurse -Force
        Write-Host "  Copied icon theme: Adwaita"
    }
    catch {
        Write-Warning "  Failed to copy Adwaita from $AdwaitaSrc : $($_.Exception.Message)"
    }
} else {
    Write-Warning "  Icon theme 'Adwaita' not found at $AdwaitaSrc"
}

# ====================================================
#  DONE
# ====================================================

Write-Host ""
Write-Host "==============================================="
Write-Host " PORTABLE GTK APP CREATED:"
Write-Host "   $OutputDir"
Write-Host " Double-click app.exe to run."
Write-Host "==============================================="
