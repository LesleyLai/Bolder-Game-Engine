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
    "${CORE_INCLUDE_PATH}/bolder/angle.hpp"
    "${CORE_SRC_PATH}/angle.cpp"
    "${CORE_INCLUDE_PATH}/bolder/date_time.hpp"
    "${CORE_SRC_PATH}/date_time.cpp"
    "${CORE_INCLUDE_PATH}/bolder/exception.hpp"
    "${CORE_SRC_PATH}/exception.cpp"
    "${CORE_INCLUDE_PATH}/bolder/file_util.hpp"
    "${CORE_SRC_PATH}/file_util.cpp"
    "${CORE_INCLUDE_PATH}/bolder/logger.hpp"
    "${CORE_SRC_PATH}/logger.cpp"
    "${CORE_INCLUDE_PATH}/bolder/math.hpp"
    "${CORE_SRC_PATH}/math.cpp"
    "${CORE_INCLUDE_PATH}/bolder/matrix.hpp"
    "${CORE_SRC_PATH}/matrix.cpp"
    "${CORE_INCLUDE_PATH}/bolder/transform.hpp"
    "${CORE_SRC_PATH}/transform.cpp"
    "${CORE_INCLUDE_PATH}/bolder/vector.hpp"
    "${CORE_SRC_PATH}/vector.cpp"
    "${CORE_INCLUDE_PATH}/bolder/system.hpp"
    "${CORE_SRC_PATH}/system.cpp"
    "${CORE_INCLUDE_PATH}/bolder/event.hpp"
    "${CORE_INCLUDE_PATH}/bolder/events/window_resize.hpp"
    )

target_link_libraries(BolderCore
  ${THIRD_PARTY_LIBS}
)

#test
if(BOLDER_WITH_TESTS)
    enable_testing ()
    add_subdirectory (test)
endif()

# IDE specific
set_property(TARGET BolderCore PROPERTY FOLDER Layers)
