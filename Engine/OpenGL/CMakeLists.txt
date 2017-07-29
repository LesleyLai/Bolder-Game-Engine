#configure directories
set (OPENGL_SRC_PATH "${CMAKE_CURRENT_SOURCE_DIR}/src")
set (OPENGL_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/include")

include_directories (
    ${OPENGL_INCLUDE_PATH}/bolder
    ${BOLDER_UTIL_INCLUDE_PATH}
    ${THIRD_PARTY_INCLUDE_PATH}
    "${THIRD_PARTY_MODULE_PATH}/glad/include")

#set sources
file (GLOB_RECURSE OPENGL_HEADER_FILES "${OPENGL_INCLUDE_PATH}/*.hpp")
file (GLOB_RECURSE OPENGL_SOURCE_FILES "${OPENGL_SRC_PATH}/*.hpp")
file (GLOB_RECURSE OPENGL_SOURCE_FILES "${OPENGL_SRC_PATH}/*.cpp")

# Platform layer
add_library (BolderOpenGL STATIC
    ${OPENGL_SOURCE_FILES} ${OPENGL_HEADER_FILES}
    "${THIRD_PARTY_MODULE_PATH}/glad/src/glad.c")

target_link_libraries (BolderOpenGL BolderUtility ${THIRD_PARTY_LIBS})

#test
if(BOLDER_WITH_TESTS)
    enable_testing ()
    add_subdirectory (test)
endif()

# Export variables
set (OPENGL_INCLUDE_PATH ${OPENGL_INCLUDE_PATH} PARENT_SCOPE)

# IDE specific
set_property(TARGET BolderOpenGL PROPERTY FOLDER Layers)
