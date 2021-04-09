cmake_minimum_required(VERSION 3.14)

project(jb_assignment_window)

include(cmake/CompileOptions.cmake)
include(cmake/Development.cmake)
include(cmake/Sanitize.cmake)

option(ASAN "Sanitize with Address Sanitizer" OFF)

add_subdirectory(lib/wheels)
add_subdirectory(lib/tiny-graphics)
add_subdirectory(src)
