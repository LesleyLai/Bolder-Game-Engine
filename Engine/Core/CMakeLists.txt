#configure directories
set (CORE_SRC_PATH "${CMAKE_CURRENT_SOURCE_DIR}/src")
set (CORE_INCLUDE_PATH
  "${CMAKE_CURRENT_SOURCE_DIR}/include")

add_library (BolderCore STATIC "")

target_include_directories(BolderCore
    PUBLIC
    ${CORE_INCLUDE_PATH}
    PRIVATE
    "${CORE_INCLUDE_PATH}/bolder"
    )

target_sources(BolderCore
    PRIVATE
    "${CORE_INCLUDE_PATH}/bolder/system.hpp"
    "${CORE_SRC_PATH}/system.cpp"
    "${CORE_INCLUDE_PATH}/bolder/event.hpp"
    "${CORE_INCLUDE_PATH}/bolder/events/input_events.hpp"
    )

target_link_libraries(BolderCore
  BolderUtil
)

#test
if(BOLDER_WITH_TESTS)
    enable_testing ()
    add_subdirectory (test)
endif()

# IDE specific
set_property(TARGET BolderCore PROPERTY FOLDER Layers)
