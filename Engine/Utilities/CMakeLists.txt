#configure directories
set (UTIL_SRC_PATH "${CMAKE_CURRENT_SOURCE_DIR}/src")
set (UTIL_INCLUDE_PATH
  "${CMAKE_CURRENT_SOURCE_DIR}/include")

add_library (BolderUtil STATIC
    "${UTIL_INCLUDE_PATH}/bolder/angle.hpp"
    "${UTIL_SRC_PATH}/angle.cpp"
    "${UTIL_INCLUDE_PATH}/bolder/date_time.hpp"
    "${UTIL_SRC_PATH}/date_time.cpp"
    "${UTIL_INCLUDE_PATH}/bolder/exception.hpp"
    "${UTIL_SRC_PATH}/exception.cpp"
    "${UTIL_INCLUDE_PATH}/bolder/file_util.hpp"
    "${UTIL_INCLUDE_PATH}/bolder/string_literal.hpp"
    "${UTIL_SRC_PATH}/file_util.cpp"
    "${UTIL_INCLUDE_PATH}/bolder/logger.hpp"
    "${UTIL_SRC_PATH}/logger.cpp"
    "${UTIL_INCLUDE_PATH}/bolder/math.hpp"
    "${UTIL_SRC_PATH}/math.cpp"
    "${UTIL_INCLUDE_PATH}/bolder/matrix.hpp"
    "${UTIL_SRC_PATH}/matrix.cpp"
    "${UTIL_INCLUDE_PATH}/bolder/transform.hpp"
    "${UTIL_SRC_PATH}/transform.cpp"
    "${UTIL_INCLUDE_PATH}/bolder/vector.hpp"
    "${UTIL_SRC_PATH}/vector.cpp"
    "${UTIL_INCLUDE_PATH}/bolder/byte.hpp"
)

target_include_directories(BolderUtil
    PUBLIC
    ${UTIL_INCLUDE_PATH}
    PRIVATE
    "${UTIL_INCLUDE_PATH}/bolder"
    )

target_link_libraries(BolderUtil stb)
