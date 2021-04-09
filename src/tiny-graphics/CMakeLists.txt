set(TARGET_NAME tiny-graphics)

add_library(${TARGET_NAME})
target_sources(${TARGET_NAME}
  PUBLIC
    glx_context.hpp
    glx_window.hpp
  PRIVATE
    glx_context.cpp
    glx_window.cpp
  )
target_link_libraries(${TARGET_NAME}
  PRIVATE
    wheels
  PUBLIC
    tiny-xlib
    tiny-opengl
  )

add_subdirectory(tiny-opengl)
add_subdirectory(tiny-xlib)
