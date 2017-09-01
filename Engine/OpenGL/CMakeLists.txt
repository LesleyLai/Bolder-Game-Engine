#configure directories
set (OPENGL_SRC_PATH "${CMAKE_CURRENT_SOURCE_DIR}/src")

add_library (BolderOpenGL
    "${OPENGL_SRC_PATH}/opengl.cpp"
    "${OPENGL_SRC_PATH}/index_buffer.hpp"
    "${OPENGL_SRC_PATH}/vertex_buffer.hpp"
    "${OPENGL_SRC_PATH}/opengl_program.hpp"
    "${OPENGL_SRC_PATH}/opengl_program.cpp"
    "${OPENGL_SRC_PATH}/opengl_shader.hpp"
    "${OPENGL_SRC_PATH}/opengl_shader.cpp"
    "${OPENGL_SRC_PATH}/opengl_vertex_array.hpp"
    "${OPENGL_SRC_PATH}/opengl_vertex_array.cpp"
    "${OPENGL_SRC_PATH}/texture.hpp"
    "${OPENGL_SRC_PATH}/texture.cpp"

    "${THIRD_PARTY_MODULE_PATH}/glad/src/glad.c")

target_include_directories (BolderOpenGL
    PRIVATE
    "${THIRD_PARTY_MODULE_PATH}/glad/include"
    )

# Platform layer
target_link_libraries (BolderOpenGL BolderGraphics)

#test
if(BOLDER_WITH_TESTS)
    enable_testing ()
    add_subdirectory (test)
endif()
