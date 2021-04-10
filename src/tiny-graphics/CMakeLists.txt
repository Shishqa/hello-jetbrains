set(TARGET_NAME tiny-graphics)

add_library(${TARGET_NAME})
target_sources(${TARGET_NAME}
  PUBLIC
    tiny_graphics.hpp
    window.hpp
  PRIVATE
    window.cpp
  )
target_link_libraries(${TARGET_NAME}
  PUBLIC
    wheels
    tiny-xlib
    tiny-opengl
  )

add_subdirectory(tiny-opengl)
add_subdirectory(tiny-xlib)
