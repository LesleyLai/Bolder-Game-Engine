include(ExternalProject)
find_package(Git REQUIRED)


#configure directories
set (THIRD_PARTY_MODULE_PATH "${PROJECT_SOURCE_DIR}/third_party")

# Boost
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
FIND_PACKAGE(Boost 1.43 COMPONENTS REQUIRED)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    set (THIRD_PARTY_INCLUDE_PATH ${Boost_INCLUDE_DIRS} ${THIRD_PARTY_INCLUDE_PATH})
else()
  message( FATAL_ERROR "Cannot find the boost C++ library."
      " The bolder game engine need boost library to build." )
endif()

set (THIRD_PARTY_INCLUDE_PATH ${THIRD_PARTY_INCLUDE_PATH} PARENT_SCOPE)

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
