#configure directories
set (APP_SRC_PATH "${CMAKE_CURRENT_SOURCE_DIR}/src")
set (APP_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/include")

# Platform layer
add_library (BolderApplication STATIC "")

target_sources(BolderApplication
    PRIVATE
    "${APP_INCLUDE_PATH}/bolder/application.hpp"
    "${APP_INCLUDE_PATH}/bolder/engine.hpp"
    "${APP_SRC_PATH}/application.cpp"
    "${APP_SRC_PATH}/engine.cpp"
    )

target_include_directories(BolderApplication
    PUBLIC
    ${APP_INCLUDE_PATH}
    PRIVATE
    ${APP_INCLUDE_PATH}/bolder
    )

target_link_libraries(BolderApplication
    BolderCore
    BolderPlatform
    BolderGraphics
    BolderOpenGL
    )

# IDE specific
set_property(TARGET BolderApplication PROPERTY FOLDER Layers)
