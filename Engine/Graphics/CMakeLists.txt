#configure directories
set (GRAPHICS_SRC_PATH "${CMAKE_CURRENT_SOURCE_DIR}/src")
set (GRAPHICS_INCLUDE_PATH
  "${CMAKE_CURRENT_SOURCE_DIR}/include")

add_library (BolderGraphics STATIC "")

target_include_directories(BolderGraphics
    PUBLIC
    ${GRAPHICS_INCLUDE_PATH}
    PRIVATE
    "${GRAPHICS_INCLUDE_PATH}/bolder"
    )

target_sources(BolderGraphics
    PRIVATE
    "${GRAPHICS_INCLUDE_PATH}/bolder/graphics_system.hpp"
    "${GRAPHICS_SRC_PATH}/graphics_system.cpp"
    "${GRAPHICS_INCLUDE_PATH}/bolder/sprite.hpp"
    )

target_link_libraries(BolderGraphics
    BolderCore
)

# IDE specific
set_property(TARGET BolderGraphics PROPERTY FOLDER Layers)
