# Dragon (Raylib C++ Project)

Hello! 👋
This is my first project using **Raylib with C++**.
---

## ⚙️ Requirements

You need:

* C++ compiler (g++, clang, or MSVC)
* Raylib installed

---

# 🐧 Linux (Ubuntu / Debian)

### Install Raylib:

```bash
sudo apt update
sudo apt install libraylib-dev
```

### Compile:

```bash
g++ main2.cpp -o game -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
```

### Run:

```bash
./game
```

---

# 🍎 macOS

### Install Raylib (Homebrew):

```bash
brew install raylib
```

### Compile:

```bash
g++ main2.cpp -o game -lraylib -framework OpenGL -framework Cocoa -framework IOKit
```

### Run:

```bash
./game
```

---

# 🪟 Windows (MinGW)

### Option 1: MSYS2 (recommended)

Install MSYS2: https://www.msys2.org/

Then in MSYS2 terminal:

```bash
pacman -S mingw-w64-x86_64-raylib
```

### Compile:

```bash
g++ main2.cpp -o game.exe -lraylib -lopengl32 -lgdi32 -lwinmm
```

### Run:

```bash
game.exe
```

---

---

## 📌 Notes

* Make sure `resource/` folder stays in the same directory as the executable
* Paths are relative, so don’t move assets unless you update code

---

## ❤️ Author

Made by a beginner learning C++ + Raylib
First step into game development 
