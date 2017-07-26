#set includes
include_directories (${BOLDER_CORE_INCLUDE_PATH})

#set target executable
add_executable (BolderDemo "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")

#add the library
target_link_libraries (BolderDemo BolderCore)

#test
enable_testing ()
add_subdirectory (test)
