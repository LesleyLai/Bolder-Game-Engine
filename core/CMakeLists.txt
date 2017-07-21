#configure variables
set (ENGINE_CORE_NAME "${PROJECT_NAME}Core")

#configure directories
set (ENGINE_CORE_MODULE_PATH "${PROJECT_SOURCE_DIR}/core")
set (ENGINE_CORE_SRC_PATH  "${ENGINE_CORE_MODULE_PATH}/src" )
set (ENGINE_CORE_INCLUDE_PATH  "${ENGINE_CORE_MODULE_PATH}/include")

# Platform abstruction layer
add_subdirectory(platform)

#set includes
include_directories ("${ENGINE_CORE_INCLUDE_PATH}/bolder"
    ${THIRD_PARTY_INCLUDE_PATH} ${PLATFORM_LAYER_INCLUDE_PATH})

#set sources
file (GLOB_RECURSE CORE_HEADER_FILES "${ENGINE_CORE_INCLUDE_PATH}/*.hpp")
file (GLOB_RECURSE CORE_SOURCE_FILES "${ENGINE_CORE_SRC_PATH}/*.hpp")
file (GLOB_RECURSE CORE_SOURCE_FILES "${ENGINE_CORE_SRC_PATH}/*.cpp")

# Engine
add_library (${ENGINE_CORE_NAME} STATIC ${CORE_SOURCE_FILES} ${CORE_HEADER_FILES})
target_link_libraries(${ENGINE_CORE_NAME}
    ${THIRD_PARTY_LIBS}
    ${PLATFORM_LAYER_NAME})

#export vars
set (ENGINE_CORE_INCLUDE_PATH ${ENGINE_CORE_INCLUDE_PATH} PARENT_SCOPE)
set (ENGINE_CORE_NAME ${ENGINE_CORE_NAME} PARENT_SCOPE)

#test
if(BOLDER_WITH_TESTS)
    enable_testing ()
    add_subdirectory (test)
endif()
