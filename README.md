# Pong

## Overview
Simple C++ remake of the classic 2D Pong in CMake using vcpkg manifest for dependencies.

## Features
- Classic Pong mechanics of vertical paddle movement, ball physics and scoring
- Light green background to minimize eye fatigue in prolonged play
- Cross-platform: Windows / macOS / Linux

## Project Structure
├─ CMakeLists.txt        # top-level CMake build
├─ CMakePresets.json     # developer-friendly configure/build presets
├─ vcpkg.json            # dependencies (manifest mode)
└─ pong/                 # game source (executable target)
   └─ main.cpp           # entry point / game loop

## Setup Instructions
### 0) Prerequisites
- **CMake 3.25+**  
- **C++17 or later** toolchain (MSVC, Clang, or GCC)  
- **vcpkg** (manifest mode). If you don’t have it:
  ```bash
  git clone https://github.com/microsoft/vcpkg.git
  ./vcpkg/bootstrap-vcpkg.sh   # macOS/Linux
  .\vcpkg\bootstrap-vcpkg.bat  # Windows
  ```
  Then set `VCPKG_ROOT` to that folder (optional but convenient).

### 1) Configure & build (with presets)
**Windows (MSVC / x64):**
```powershell
cmake --preset=default
cmake --build --preset=release
.\build\pong\Release\pong.exe
```
**macOS / Linux:**
```bash
cmake --preset=default
cmake --build --preset=release
./build/pong/pong
```
## Controls
- **↑ / ↓** – Right paddle up/down   
- **Esc** – Quit

## Roadmap for Future Works
- Option to add Two-player modes
- Sound effects and music
- Items and modifiers
- Obstacles
- Menu & pause overlay  
- Configurable controls & difficulty  
- Unit tests for ball/paddle physics

## Contact
If there are any questions or suggestions for improving this repository, please do not hesitate to contact me at joh78@gatech.edu.
Thank you.