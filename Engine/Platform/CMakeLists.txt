#configure directories
set (PLATFORM_SRC_PATH "${CMAKE_CURRENT_SOURCE_DIR}/src")
set (PLATFORM_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/include")

include_directories (
    ${PLATFORM_INCLUDE_PATH}/bolder
    ${BOLDER_UTIL_INCLUDE_PATH}
    ${THIRD_PARTY_INCLUDE_PATH})

#set sources
file (GLOB_RECURSE PLATFORM_HEADER_FILES "${PLATFORM_INCLUDE_PATH}/*.hpp")
file (GLOB_RECURSE PLATFORM_SOURCE_FILES "${PLATFORM_SRC_PATH}/*.hpp")
file (GLOB_RECURSE PLATFORM_SOURCE_FILES "${PLATFORM_SRC_PATH}/*.cpp")

# Platform layer
add_library (BolderPlatform STATIC
    ${PLATFORM_SOURCE_FILES} ${PLATFORM_HEADER_FILES})

target_link_libraries (BolderPlatform BolderUtility ${THIRD_PARTY_LIBS})

# Export variables
set (PLATFORM_INCLUDE_PATH ${PLATFORM_INCLUDE_PATH} PARENT_SCOPE)

# IDE specific
set_property(TARGET BolderPlatform PROPERTY FOLDER Layers)
