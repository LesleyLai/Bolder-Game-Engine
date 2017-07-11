include(ExternalProject)
find_package(Git REQUIRED)


#configure directories
set (THIRD_PARTY_MODULE_PATH "${PROJECT_SOURCE_DIR}/third_party")

# Doctest
set(DOCTEST_INCLUDE_DIR "${THIRD_PARTY_MODULE_PATH}/doctest")

#set variables for tests
set (TEST_THIRD_PARTY_INCLUDE_PATH ${DOCTEST_INCLUDE_DIR})

#export vars
set (TEST_THIRD_PARTY_INCLUDE_PATH ${TEST_THIRD_PARTY_INCLUDE_PATH} PARENT_SCOPE)
