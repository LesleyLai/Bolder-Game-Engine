include(../scripts/cmake/compiler.cmake)

# Engine core functionalities
add_subdirectory(Core)

# Graphics Module
add_subdirectory(Graphics)

# Platform abstruction layer
add_subdirectory(Platform)

# Thin OpenGL Wrapper
add_subdirectory(OpenGL)

# Application entry base class
add_subdirectory(Application)

# Default assets for game
add_subdirectory(Assets)

if(BOLDER_WITH_TESTS)
    enable_testing()
endif()
