set(TARGET_NAME tiny-gl-wrapper)
set(INCROOT ${PROJECT_SOURCE_DIR}/src/tiny-gl-wrapper)

add_library(${TARGET_NAME})
target_sources(${TARGET_NAME}
  PUBLIC
    color.hpp
    gl_impl.hpp
    shader.hpp
  PRIVATE
    shader.cpp
    gl_impl.cpp
  )
target_link_libraries(${TARGET_NAME}
  PRIVATE
    wheels
    GL GLU GLEW
  )
target_include_directories(${TARGET_NAME}
  PRIVATE
    ${INCROOT}
    ${PROJECT_SOURCE_DIR}/lib/
  )
