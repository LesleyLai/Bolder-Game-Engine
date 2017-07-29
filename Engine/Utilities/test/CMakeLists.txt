#set includes
include_directories (${TEST_THIRD_PARTY_INCLUDE_PATH})

#set test sources
file (GLOB TEST_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

#set target executable
add_executable (BolderUtilityTest ${TEST_SOURCE_FILES})

add_test(NAME BolderUtilityTest COMMAND BolderUtilityTest)

target_link_libraries(BolderUtilityTest BolderUtility)

# Turn on CMake testing capabilities
enable_testing()
