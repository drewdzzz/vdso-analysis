file(GLOB_RECURSE PUBLIC_INCLUDES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp"
)
file(GLOB_RECURSE SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

function(create_case)
  cmake_parse_arguments(
    CASE
    ""
    "PREFIX"
    "SOURCES"
    ${ARGN}
  )
  message(STATUS "Creating case ${CASE_PREFIX}.case")
  add_executable(${CASE_PREFIX}.case ${CASE_SOURCES})
  target_link_libraries(${CASE_PREFIX}.case utils)
  target_include_directories(${CASE_PREFIX}.case PUBLIC ${COMMON_INCLUDES})
endfunction()

create_case(PREFIX map_simple SOURCES map_simple.cpp)
create_case(PREFIX map_cache_intensive SOURCES map_cache_intensive.cpp)
