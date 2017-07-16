cmake_minimum_required (VERSION 3.3)

project (BolderGameEngine)

set_property (GLOBAL PROPERTY USE_FOLDERS ON)

set (CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

option(BOLDER_WITH_TESTS "Build tests of Bolder Game Engine" ON)
option(BOLDER_WITH_DEMOS "Build demos of Bolder Game Engine" ON)

add_subdirectory (third_party EXCLUDE_FROM_ALL)

include(scripts/cmake/compiler.cmake)

add_subdirectory (lib)

if(BOLDER_WITH_DEMOS)
    add_subdirectory (demo)
endif ()

# Documents
if (CMAKE_BUILD_TYPE MATCHES "^[Rr]elease")
    include(scripts/cmake/doxygen.cmake)
endif ()


enable_testing ()
