#set includes
set (UTIL_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/include")
set (UTIL_SRC "${CMAKE_CURRENT_SOURCE_DIR}/src")
include_directories ("${UTIL_INCLUDE}/bolder")

#set sources
file (GLOB_RECURSE UTIL_HEADER_FILES "${UTIL_INCLUDE}/*.hpp")
file (GLOB_RECURSE UTIL_SOURCE_FILES "${UTIL_SRC}/*.hpp")
file (GLOB_RECURSE UTIL_SOURCE_FILES "${UTIL_SRC}/*.cpp")

# Engine
add_library (BolderUtility STATIC ${UTIL_SOURCE_FILES} ${UTIL_HEADER_FILES})

#test
if(BOLDER_WITH_TESTS)
    enable_testing ()
    add_subdirectory (test)
endif()

# IDE specific
set_property(TARGET BolderUtility PROPERTY FOLDER Layers)

# export variables
set (BOLDER_UTIL_INCLUDE_PATH "${UTIL_INCLUDE}" PARENT_SCOPE)
