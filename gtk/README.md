# GTK4 + VS Code Starter

Minimal GTK4 app wired for VS Code tasks & debugging.

## Prereqs

### Windows (MSYS2, 64-bit)
1) Install MSYS2 from https://www.msys2.org
2) Open **MSYS2 MINGW64** and run:
   ```bash
   pacman -Syu
   pacman -Su
   pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-gtk4 pkgconf gdb
   ```
3) Navigate to this folder (see "MSYS2 path cheatsheet" below) and run:
   ```bash
   code .
   ```

### Ubuntu/Debian
```bash
sudo apt update
sudo apt install build-essential pkg-config libgtk-4-dev gdb
```

### macOS (Homebrew)
```bash
brew install gtk4 pkg-config gcc gdb
```
> For debugging on macOS, you may prefer `lldb`:
> edit `.vscode/launch.json` → `"MIMode": "lldb"`, `"miDebuggerPath": "lldb"`.

## Build & Run
In VS Code:
- **Terminal → Run Task…** → **run (Linux/macOS)** or **run (Windows MSYS2)**.
- Or press **F5** to debug with **Launch GTK4 App (gdb)**.

## MSYS2 path cheatsheet (Windows)
- Windows drives are mounted as `/c`, `/d`, etc.
- Examples:
  ```bash
  cd /c/Users/$USERNAME/Downloads
  cd "/c/Users/$USERNAME/My Projects/gtk4-vscode-starter"
  ls
  pwd
  ```
- Tips:
  - Use quotes for folders with spaces.
  - Tab-completion works (`cd /c/Use<Tab>`).
  - From this folder, run `code .` to open VS Code in the right environment.

## Notes
- The sample uses GTK4's `GtkApplication` and `gtk_window_set_child()`.
- If `pkg-config` can't find gtk4, ensure MSYS2 **MINGW64** shell is used and
  `mingw64/bin` is first in PATH (opening VS Code with `code .` from MINGW64 ensures that).
