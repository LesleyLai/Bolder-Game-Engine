file(COPY "shaders/sprite.vert" DESTINATION "${CMAKE_BINARY_DIR}/demo")
file(COPY "shaders/sprite.frag" DESTINATION "${CMAKE_BINARY_DIR}/demo")

file(COPY "textures/container.jpg" DESTINATION "${CMAKE_BINARY_DIR}/demo/textures")


add_custom_target(BolderAsserts
    SOURCES
    "shaders/sprite.vert"
    "shaders/sprite.frag")
