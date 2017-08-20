include(../scripts/cmake/compiler.cmake)

# Engien core functionalities
add_subdirectory(Core)

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

# Export variables
set (BOLDER_APP_INCLUDE_PATH "${BOLDER_APP_INCLUDE_PATH}" PARENT_SCOPE)
