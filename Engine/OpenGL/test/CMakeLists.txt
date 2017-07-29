#set includes
include_directories (${TEST_THIRD_PARTY_INCLUDE_PATH})

#set test sources
file (GLOB TEST_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

#set target executable
add_executable (BolderOpenGLTest ${TEST_SOURCE_FILES})

add_test(NAME BolderOpenGLTest COMMAND BolderOpenGLTest)

target_link_libraries(BolderOpenGLTest BolderOpenGL)

# Turn on CMake testing capabilities
enable_testing()
