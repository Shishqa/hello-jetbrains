cmake_minimum_required(VERSION 3.14)

project(jb_assignment_window)

option(ASAN "Sanitize with Address Sanitizer" OFF)

include(cmake/CompileOptions.cmake)
include(cmake/Development.cmake)
include(cmake/Sanitize.cmake)

add_subdirectory(src)
