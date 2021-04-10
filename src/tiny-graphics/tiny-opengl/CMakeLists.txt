set(TARGET_NAME tiny-opengl)

add_library(${TARGET_NAME})
target_sources(${TARGET_NAME}
  PUBLIC
    color.hpp
    gl_impl.hpp
    shader.hpp
    program.hpp
  PRIVATE
    shader.cpp
    program.cpp
    gl_impl.cpp
  )
target_link_libraries(${TARGET_NAME}
  PRIVATE
    wheels
    GL GLU GLEW
  )
