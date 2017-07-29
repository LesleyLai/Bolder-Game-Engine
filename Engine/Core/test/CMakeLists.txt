#set includes
include_directories (${TEST_THIRD_PARTY_INCLUDE_PATH})

#set test sources
file (GLOB TEST_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

#set target executable
add_executable (BolderCoreTest ${TEST_SOURCE_FILES})

add_test(NAME BolderCoreTest COMMAND BolderCoreTest)

target_link_libraries(BolderCoreTest BolderCore)

# Turn on CMake testing capabilities
enable_testing()
