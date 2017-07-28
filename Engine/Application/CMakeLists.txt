#configure directories
set (APP_SRC_PATH "${CMAKE_CURRENT_SOURCE_DIR}/src")
set (APP_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/include")

include_directories (
    ${BOLDER_CORE_INCLUDE_PATH}
    ${APP_INCLUDE_PATH}/bolder)

#set sources
file (GLOB_RECURSE APP_HEADER_FILES "${APP_INCLUDE_PATH}/*.hpp")
file (GLOB_RECURSE APP_SOURCE_FILES "${APP_SRC_PATH}/*.hpp")
file (GLOB_RECURSE APP_SOURCE_FILES "${APP_SRC_PATH}/*.cpp")

# Platform layer
add_library (BolderApplication STATIC
    ${APP_SOURCE_FILES} ${APP_HEADER_FILES})

target_link_libraries (BolderApplication BolderCore)

# Export variables
set (BOLDER_APP_INCLUDE_PATH
    ${APP_INCLUDE_PATH}
    ${BOLDER_CORE_INCLUDE_PATH}
    PARENT_SCOPE)

# IDE specific
set_property(TARGET BolderApplication PROPERTY FOLDER Layers)
