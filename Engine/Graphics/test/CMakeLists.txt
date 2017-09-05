add_executable (BolderGraphicsTest "")

target_sources(BolderGraphicsTest
    PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/sprite_test.cpp"
    )

add_test(NAME BolderGraphicsTest COMMAND BolderGraphicsTest)

target_link_libraries(BolderGraphicsTest BolderGraphics BolderTestLib)

# Turn on CMake testing capabilities
enable_testing()
