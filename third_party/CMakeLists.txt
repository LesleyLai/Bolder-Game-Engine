#configure directories
set (THIRD_PARTY_MODULE_PATH "${PROJECT_SOURCE_DIR}/third_party")

# GLFW
include(../scripts/cmake/SetGLFW.cmake)
add_subdirectory(glfw)

# stb
set (STB_INCLUDE_PATH "${THIRD_PARTY_MODULE_PATH}/stb/include")

add_library(STB INTERFACE)
target_include_directories(STB SYSTEM INTERFACE "${STB_INCLUDE_PATH}")

# Export include paths
set (THIRD_PARTY_MODULE_PATH "${THIRD_PARTY_MODULE_PATH}" PARENT_SCOPE)

# Unit test framework
if(BOLDER_WITH_TESTS)
    set(DOCTEST_INCLUDE_DIR "${THIRD_PARTY_MODULE_PATH}/doctest/doctest" CACHE INTERNAL
        "Path to include folder for doctest")

    #set variables for tests
    set (TEST_THIRD_PARTY_INCLUDE_PATH ${DOCTEST_INCLUDE_DIR})

    add_library(BolderTestLib INTERFACE)
    target_include_directories(BolderTestLib SYSTEM INTERFACE "${DOCTEST_INCLUDE_DIR}")


endif(BOLDER_WITH_TESTS)
