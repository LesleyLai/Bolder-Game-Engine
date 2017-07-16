**Bolder** is a game engine. The project just started, so it is far from useful.

The medium-term task of Bolder is a small cross-platform 2d game engine.

# Build #
To build **bolder game engine**, you need to install [git](https://git-scm.com/), and [CMake](https://cmake.org/) to your computer. 

Also, the engine depends on [Boost C++ Library](http://www.boost.org/).

# Contribution #
[Todo.org](./Todo.org) contains the current todo list.

# Build status #
| Platform | Status |
|-----------|-------|
| Windows   |[![AppVeyor](https://img.shields.io/appveyor/ci/LesleyLai/bolder-game-engine.svg)](https://ci.appveyor.com/project/LesleyLai/bolder-game-engine) |
| Linux/Mac | [![Travis](https://img.shields.io/travis/LesleyLai/Bolder-Game-Engine.svg)](https://travis-ci.org/LesleyLai/Bolder-Game-Engine) |


# Project Structure #
``` c
/lib
  /src
    /bolder
  /include
    /bolder
  /platform // platform dependent codes
  /test // unit test for the engine
/docs // Documents
/demo
  /src
  /test
/third_party
/scripts // Misc scripts
```
