#configure directories
set (GRAPHICS_SRC_PATH "${CMAKE_CURRENT_SOURCE_DIR}/src")
set (GRAPHICS_INCLUDE_PATH
  "${CMAKE_CURRENT_SOURCE_DIR}/include")

add_library (BolderGraphics STATIC "")

target_include_directories(BolderGraphics
    PUBLIC
    ${GRAPHICS_INCLUDE_PATH}
    PRIVATE
    "${GRAPHICS_INCLUDE_PATH}/bolder/graphics"
    )

target_sources(BolderGraphics
    PRIVATE
    "${GRAPHICS_INCLUDE_PATH}/bolder/graphics/draw_call.hpp"
    "${GRAPHICS_INCLUDE_PATH}/bolder/graphics/renderer.hpp"
    "${GRAPHICS_SRC_PATH}/renderer.cpp"
    "${GRAPHICS_INCLUDE_PATH}/bolder/graphics/backend.hpp"
    "${GRAPHICS_INCLUDE_PATH}/bolder/graphics/sprite.hpp"
    "${GRAPHICS_INCLUDE_PATH}/bolder/graphics/image.hpp"
    "${GRAPHICS_SRC_PATH}/image.cpp"
    "${GRAPHICS_INCLUDE_PATH}/bolder/graphics/resource_handles.hpp"
    )

target_link_libraries(BolderGraphics BolderCore)

# IDE specific
set_property(TARGET BolderGraphics PROPERTY FOLDER Layers)
