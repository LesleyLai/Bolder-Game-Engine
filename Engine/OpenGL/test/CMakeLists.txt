# unit and integration tests of OpenGL

#set target executable
add_executable(BolderOpenGLTest "")

target_sources(BolderOpenGLTest
    PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/shader_test.cpp"
    )

target_include_directories (BolderOpenGLTest
    PRIVATE
    ${TEST_THIRD_PARTY_INCLUDE_PATH}
    "${THIRD_PARTY_MODULE_PATH}/glad/include"
    )

add_test(NAME BolderOpenGLTest COMMAND BolderOpenGLTest)

target_link_libraries(BolderOpenGLTest BolderOpenGL)

# Turn on CMake testing capabilities
enable_testing()
