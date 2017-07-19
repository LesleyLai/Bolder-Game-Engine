set (DEMO_NAME "${PROJECT_NAME}Demo")

#configure directories
set (DEMO_MODULE_PATH "${PROJECT_SOURCE_DIR}/demo")
set (DEMO_SRC_PATH "${DEMO_MODULE_PATH}/src" )

#set includes
include_directories (${ENGINE_CORE_INCLUDE_PATH})

#set target executable
add_executable (${DEMO_NAME} "${DEMO_SRC_PATH}/main.cpp")

#add the library
target_link_libraries (${DEMO_NAME} ${ENGINE_CORE_NAME})

#test
enable_testing ()
add_subdirectory (test)
