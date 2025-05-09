# Daily Quote In C
Get a daily qoute or add your own quotes if that what you like. Simple program in C

---

## Install Compiler

This guide will help you install a C/C++ compiler (GCC or Clang) on your system.

---

### 🪟 Windows (GCC via MinGW-w64)

1. Download MinGW-w64 from [this link](https://sourceforge.net/projects/mingw-w64/).
    
2. Run the downloaded `.exe` file.
    
3. During setup:
    
    - Click **Next**.
        
    - Set **Architecture** to `x86_64`.
        
    - Click **Next**.
        
    - Copy the path of the **Destination Folder** (you’ll need it later).
        
    - Click **Next** twice, then **Finish**.
        
4. Add GCC to your system PATH:
    
    - Open **Control Panel** → **System and Security** → **System**.
        
    - Click **Advanced system settings**.
        
    - Under the **Advanced** tab, click **Environment Variables**.
        
    - In the **System variables** section, find and edit `Path`.
        
    - Click **New**, then paste the path you copied earlier and add `\mingw64\bin` at the end.
        
    - Click **OK** to close all dialogs.
        

#### ▶️ Configure in VS Code

1. Open **Terminal** in VS Code.
    
2. Run:  
    **Terminal → Configure Default Build Task → Select GCC Compiler**
    
---

### 🍎 macOS (Clang)

1. Open the **Terminal**.
    
2. Check if Clang is already installed:
    
``` bash
clang --version
```
    
3. If not installed, run:
``` bash
xcode-select --install
```

