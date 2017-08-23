include(../scripts/cmake/compiler.cmake)

# Engine core functionalities
add_subdirectory(Core)

# Graphics Module
add_subdirectory(Graphics)

option(BOLDER_OPENGL_BACKEND "Generate code for OpenGL graphics backend" ON)
if (BOLDER_OPENGL_BACKEND)
    add_subdirectory(OpenGL)
endif()

# Platform abstruction layer
add_subdirectory(Platform)

# Application entry base class
add_subdirectory(Application)

# Default assets for game
add_subdirectory(Assets)

if(BOLDER_WITH_TESTS)
    enable_testing()
endif()
