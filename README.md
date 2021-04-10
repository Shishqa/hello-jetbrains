# Hello, JetBrains!

## The task

Create an app, which will create a single-window filled with color #25854b on startup. On mouse clicked a triangle should appear in the window. One of the triangle’s vertices should match with the cursor position. When the mouse is moved with the button pressed, the triangle should move with the cursor. The application should finish correctly on the closing window via window manager and should not break with a segfault on changing window dimensions.

![usage](./utility/usage.gif)

## Prerequisites

- Linux distribution 
  (Tested on Arch Linux 5.10.25-1-lts. Probably, every Linux distro would be good)
- Xlib
- OpenGL
- GLEW
- C++ compiler (gcc, clang, ...)
- CMake

```bash
# Arch
sudo pacman -S gcc cmake glew glu libx11

# Ubuntu:
sudo apt-get install build-essential cmake libgl1-mesa-dev libglu1-mesa-dev libgl-dev libglew-dev libx11-dev
```

## Building

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

## Running

```bash
cd <repo-root>
./bin/hello-jetbrains
```

## Design

Read the [DESIGN.md](./DESIGN.md) document
