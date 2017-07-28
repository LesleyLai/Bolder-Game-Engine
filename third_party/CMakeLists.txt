include(ExternalProject)
find_package(Git REQUIRED)

#configure directories
set (THIRD_PARTY_MODULE_PATH "${PROJECT_SOURCE_DIR}/third_party")

# GLAD
set (GLAD_MODULE_PATH "${THIRD_PARTY_MODULE_PATH}/glad")
set (GLAD_INCLUDE_DIR "${GLAD_MODULE_PATH}/include")

# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(glfw)

set(GLFW_Lib glfw)

set (GLFW_MODULE_PATH "${THIRD_PARTY_MODULE_PATH}/glfw")
set (GLFW_INCLUDE_DIR "${GLFW_MODULE_PATH}/include")
set (THIRD_PARTY_LIBS glfw ${THIRD_PARTY_LIBS})

set (THIRD_PARTY_INCLUDE_PATH ${GLFW_INCLUDE_DIR} ${THIRD_PARTY_INCLUDE_PATH})

# Export include paths
set (THIRD_PARTY_INCLUDE_PATH ${THIRD_PARTY_INCLUDE_PATH} PARENT_SCOPE)
set (THIRD_PARTY_LIBS ${THIRD_PARTY_LIBS} PARENT_SCOPE)
set (THIRD_PARTY_MODULE_PATH "${THIRD_PARTY_MODULE_PATH}" PARENT_SCOPE)


# Unit test framework
if(BOLDER_WITH_TESTS)
    ExternalProject_Add(
        doctest
        PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/doctest
        GIT_REPOSITORY https://github.com/onqtam/doctest.git
        TIMEOUT 10
        UPDATE_COMMAND ${GIT_EXECUTABLE} pull
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND ""
        LOG_DOWNLOAD ON
        )

    # Expose required variable (DOCTEST_INCLUDE_DIR) to parent scope
    ExternalProject_Get_Property(doctest source_dir)
    set(DOCTEST_INCLUDE_DIR ${source_dir}/doctest CACHE INTERNAL
        "Path to include folder for doctest")

    #set variables for tests
    set (TEST_THIRD_PARTY_INCLUDE_PATH ${DOCTEST_INCLUDE_DIR})

    #export vars
    set (TEST_THIRD_PARTY_INCLUDE_PATH ${TEST_THIRD_PARTY_INCLUDE_PATH} PARENT_SCOPE)
endif(BOLDER_WITH_TESTS)
