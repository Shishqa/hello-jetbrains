set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  
  if(MSVC)
    add_compile_options(/W3 /WX)
  else()
    add_compile_options(-Wall -Wextra -Wpedantic -Werror -pedantic-errors
                        -g -fno-omit-frame-pointer -fstack-protector)
  endif()

  message(STATUS "C++ standard: ${CMAKE_CXX_STANDARD}")

endif()
