#configure directories
set (PLATFORM_SRC_PATH "${CMAKE_CURRENT_SOURCE_DIR}/src")
set (PLATFORM_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/include")

# Platform layer
add_library (BolderPlatform STATIC "")

target_sources (BolderPlatform
    PRIVATE
    "${PLATFORM_INCLUDE_PATH}/bolder/display.hpp"
    "${PLATFORM_INCLUDE_PATH}/bolder/input.hpp"
    "${PLATFORM_SRC_PATH}/display_glfw.cpp"
    )

target_include_directories(BolderPlatform
    PUBLIC
    ${PLATFORM_INCLUDE_PATH}
    PRIVATE
    ${PLATFORM_INCLUDE_PATH}/bolder
    )



if (WIN32)
    target_link_libraries (BolderPlatform glfw)
elseif(UNIX)
    target_link_libraries (BolderPlatform glfw)
else()
  message(FATAL_ERROR "Unsupported platform." )
endif()

target_link_libraries (BolderPlatform BolderCore)

# IDE specific
set_property(TARGET BolderPlatform PROPERTY FOLDER Layers)
