set(TARGET_NAME tiny-graphics)
set(INCROOT ${PROJECT_SOURCE_DIR}/lib/tiny-graphics)

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
    tiny-x-wrapper
    tiny-gl-wrapper
  )
target_include_directories(${TARGET_NAME}
  PRIVATE
    ${INCROOT}
    ${X11_INCLUDE_DIRECTORY}
    ${PROJECT_SOURCE_DIR}/lib/
  )

add_subdirectory(tiny-gl-wrapper)
add_subdirectory(tiny-x-wrapper)
