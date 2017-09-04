add_executable (BolderCoreTest "")

target_sources(BolderCoreTest
    PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/entity_test.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/event_test.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/handle_test.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
    )

add_test(NAME BolderCoreTest COMMAND BolderCoreTest)

target_link_libraries(BolderCoreTest BolderCore BolderTestLib)

# Turn on CMake testing capabilities
enable_testing()
