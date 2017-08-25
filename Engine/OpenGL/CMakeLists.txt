#configure directories
set (OPENGL_SRC_PATH "${CMAKE_CURRENT_SOURCE_DIR}/src")
set (OPENGL_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/include")

add_library (BolderOpenGL
    "${OPENGL_INCLUDE_PATH}/bolder/opengl_buffer.hpp"
    "${OPENGL_SRC_PATH}/opengl_buffer.cpp"
    "${OPENGL_SRC_PATH}/opengl_graphics_system_backend.cpp"
    "${OPENGL_INCLUDE_PATH}/bolder/opengl_program.hpp"
    "${OPENGL_SRC_PATH}/opengl_program.cpp"
    "${OPENGL_INCLUDE_PATH}/bolder/opengl_shader.hpp"
    "${OPENGL_SRC_PATH}/opengl_shader.cpp"
    "${OPENGL_INCLUDE_PATH}/bolder/opengl_vertex_array.hpp"
    "${OPENGL_SRC_PATH}/opengl_vertex_array.cpp"
    "${OPENGL_INCLUDE_PATH}/bolder/opengl_texture.hpp"
    "${OPENGL_SRC_PATH}/opengl_texture.cpp"

    "${THIRD_PARTY_MODULE_PATH}/glad/src/glad.c")

target_include_directories (BolderOpenGL
    PUBLIC
    ${OPENGL_INCLUDE_PATH}
    PRIVATE
    ${OPENGL_INCLUDE_PATH}/bolder
    "${THIRD_PARTY_MODULE_PATH}/glad/include"
    )

# Platform layer
target_link_libraries (BolderOpenGL BolderGraphics)

#test
if(BOLDER_WITH_TESTS)
    enable_testing ()
    add_subdirectory (test)
endif()
