file(COPY "shaders/sprite.vert" DESTINATION "${CMAKE_BINARY_DIR}/demo")
file(COPY "shaders/sprite.frag" DESTINATION "${CMAKE_BINARY_DIR}/demo")

add_custom_target(BolderAsserts
    SOURCES
    "shaders/sprite.vert"
    "shaders/sprite.frag")
