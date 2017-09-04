add_executable (BolderUtilTest "")

target_sources(BolderUtilTest
    PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/angle_test.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/logger_test.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/math_test.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/matrix_test.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/string_literal_test.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/transform_test.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/vector_test.cpp"
    )

add_test(NAME BolderUtilTest COMMAND BolderUtilTest)

target_link_libraries(BolderUtilTest BolderUtil BolderTestLib)

# Turn on CMake testing capabilities
enable_testing()
