#set target executable
add_executable (BolderDemo "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")

#add the library
target_link_libraries (BolderDemo BolderApplication)

#test
enable_testing ()
add_subdirectory (test)
