**Bolder** is a game engine. The project just started, so it is far from useful.

The medium-term task of Bolder is a small cross-platform 2d game engine.

# Build #
To build **bolder game engine**, you need to install [git](https://git-scm.com/), and [CMake](https://cmake.org/) to your computer. 

For linux, you need gcc 6+ or clang to compiler the codes. For Windows, Microsoft Visual Studio 2015 and 2017 are supported. Previous versions of MSVC cannot compile the engine.

# Contribution #
[Todo.org](./Todo.org) contains the current todo list.

# Build status #
| Platform | Status |
|-----------|-------|
| Windows   |[![AppVeyor](https://img.shields.io/appveyor/ci/LesleyLai/bolder-game-engine.svg)](https://ci.appveyor.com/project/LesleyLai/bolder-game-engine) |
| Linux/Mac | [![Travis](https://img.shields.io/travis/LesleyLai/Bolder-Game-Engine.svg)](https://travis-ci.org/LesleyLai/Bolder-Game-Engine) |


# Project Structure #
``` c
/Engine // Modules of the engine
  /Application // provides Application class that all games should inherent from
  /Core // Core engine codes
  /Utilities // Utilities and math libraries that other parts of engine depend on
  /Platform // Platform specific codes and a platform-agnostic interface for such codes
  /OpenGL // A thin OpenGL wrapper

/docs // Documents
/demo // Demo about how to use the engine
/third_party
/scripts // Misc scripts
```
