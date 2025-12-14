# ================================================
#  PORTABLE PACKAGE BUILDER FOR GTKmm 4 (MSYS2)
# ================================================

# ---- CONFIG ----
$MsysRoot    = "C:\msys64"
$SrcBin      = Join-Path $MsysRoot "mingw64\bin"
$SrcShare    = Join-Path $MsysRoot "mingw64\share"
$SrcLib      = Join-Path $MsysRoot "mingw64\lib"

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
#  COPY DLL DEPENDENCIES
# ====================================================

$dlls = @(
    "libcairomm-1.16-1.dll",
    "libgiomm-2.68-1.dll",
    "libglibmm-2.68-1.dll",
    "libgcc_s_seh-1.dll",
    "libpango-1.0-0.dll",
    "libgtkmm-4.0-0.dll",
    "libsigc-3.0-0.dll",
    "libpangocairo-1.0-0.dll",
    "libstdc++-6.dll",
    "libwinpthread-1.dll",
    "libcairo-2.dll",
    "libgobject-2.0-0.dll",
    "libglib-2.0-0.dll",
    "libgio-2.0-0.dll",
    "libgmodule-2.0-0.dll",
    "libfribidi-0.dll",
    "libthai-0.dll",
    "libharfbuzz-0.dll",
    "libcairo-gobject-2.dll",
    "libfontconfig-1.dll",
    "libpangowin32-1.0-0.dll",
    "libpangoft2-1.0-0.dll",
    "libgdk_pixbuf-2.0-0.dll",
    "libgraphene-1.0-0.dll",
    "libpangomm-2.48-1.dll",
    "libffi-8.dll",
    "libintl-8.dll",
    "libgtk-4-1.dll",
    "libfreetype-6.dll",
    "libpixman-1-0.dll",
    "libpng16-16.dll",
    "zlib1.dll",
    "libpcre2-8-0.dll",
    "libdatrie-1.dll",
    "libgraphite2.dll",
    "libexpat-1.dll",
    "libtiff-6.dll",
    "libjpeg-8.dll",
    "libiconv-2.dll",
    "libbrotlidec.dll",
    "libcairo-script-interpreter-2.dll",
    "libharfbuzz-subset-0.dll",
    "libepoxy-0.dll",
    "libbz2-1.dll",
    "libdeflate.dll",
    "libjbig-0.dll",
    "libLerc.dll",
    "liblzma-5.dll",
    "libwebp-7.dll",
    "libzstd.dll",
    "liblzo2-2.dll",
    "libsharpyuv-0.dll",
    "libbrotlicommon.dll",
    # SVG support:
    "librsvg-2-2.dll",
    "libxml2-2.dll"
)

Write-Host ""
Write-Host "Copying DLLs..."
foreach ($dll in $dlls) {
    $src = Join-Path $SrcBin $dll
    $dst = Join-Path $OutputDir $dll

    if (Test-Path $src) {
        Copy-Item $src $dst -Force
        Write-Host "  Copied $dll"
    } else {
        Write-Warning "  Missing DLL in $SrcBin -> $dll"
    }
}


# ====================================================
#  COPY GLIB SCHEMAS  (Fixes: No GSettings schemas installed)
# ====================================================

$SchemaSrc = Join-Path $SrcShare "glib-2.0\schemas"
$SchemaDst = Join-Path $OutputDir "share\glib-2.0\schemas"

Write-Host ""
Write-Host "Copying GLib schemas..."
if (!(Test-Path $SchemaDst)) {
    New-Item -ItemType Directory -Path $SchemaDst -Force | Out-Null
}
Copy-Item $SchemaSrc $SchemaDst -Recurse -Force


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
#  COPY ICON THEMES (Adwaita only, skip hicolor)
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
