cmake_minimum_required (VERSION 3.3)

project (BolderGameEngine)

set_property (GLOBAL PROPERTY USE_FOLDERS ON)

set (CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

# Less verbose generated make file
set_property(GLOBAL PROPERTY RULE_MESSAGES OFF)

option(BOLDER_WITH_TESTS "Build tests of Bolder Game Engine" ON)
option(BOLDER_WITH_DEMOS "Build demos of Bolder Game Engine" ON)
option(BOLDER_LOGGING_VERBOSE
    "More verbose logging and output debug logging to standard out" ON)

if(BOLDER_LOGGING_VERBOSE)
    add_definitions(-DBOLDER_LOGGING_VERBOSE=1)
endif()

add_subdirectory (third_party EXCLUDE_FROM_ALL)

add_subdirectory (Engine)

if(BOLDER_WITH_DEMOS)
    add_subdirectory (demo)
endif ()

# Documents
if (CMAKE_BUILD_TYPE MATCHES "^[Rr]elease")
    include(scripts/cmake/doxygen.cmake)
endif ()

enable_testing ()
