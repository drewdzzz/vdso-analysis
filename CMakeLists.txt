cmake_minimum_required(VERSION 3.15)

project(vdso-analysis LANGUAGES C CXX VERSION 1.0.0.0)

# Only Release build is needed for benchmarks.
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

add_definitions(-DTIMER_MODE)
add_subdirectory(src)
