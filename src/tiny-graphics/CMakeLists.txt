set(TARGET_NAME tiny-graphics)

add_library(${TARGET_NAME})
target_sources(${TARGET_NAME}
  PUBLIC
    tiny_graphics.hpp
  PRIVATE
    window.hpp
    window.cpp
  )
target_link_libraries(${TARGET_NAME}
  PUBLIC
    wheels
  PRIVATE
    tiny-xlib
    tiny-opengl
  )
target_include_directories(${TARGET_NAME}
  PUBLIC
    ${PROJECT_SOURCE_DIR}/src/
  )

add_subdirectory(tiny-opengl)
add_subdirectory(tiny-xlib)
