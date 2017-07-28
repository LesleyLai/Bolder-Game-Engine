#configure directories
set (CORE_INCLUDE_PATH
  "${CMAKE_CURRENT_SOURCE_DIR}/include"
  "${BOLDER_UTIL_INCLUDE_PATH}")

#set includes
include_directories (
  "${CORE_INCLUDE_PATH}"
  ${THIRD_PARTY_INCLUDE_PATH}
  ${PLATFORM_INCLUDE_PATH}
  ${OPENGL_INCLUDE_PATH})

#set sources
file (GLOB_RECURSE CORE_HEADER_FILES "${CORE_INCLUDE_PATH}/*.hpp")
file (GLOB_RECURSE CORE_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")
file (GLOB_RECURSE CORE_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# Engine
add_library (BolderCore STATIC
  ${CORE_SOURCE_FILES} ${CORE_HEADER_FILES})

target_link_libraries(BolderCore
  ${THIRD_PARTY_LIBS}
  BolderUtility
  BolderPlatform
  BolderOpenGL)

#test
if(BOLDER_WITH_TESTS)
    enable_testing ()
    add_subdirectory (test)
endif()

# IDE specific
set_property(TARGET BolderCore PROPERTY FOLDER Layers)

# Export variables
set (BOLDER_CORE_INCLUDE_PATH "${CORE_INCLUDE_PATH}" PARENT_SCOPE)
