set(TARGET_NAME xlib-window)

add_executable(${TARGET_NAME}
    main.cpp
    simple_window.cpp
    simple_window.hpp
    simple_triangle.cpp
    simple_triangle.hpp
  )

target_link_libraries(${TARGET_NAME}
  PRIVATE
    wheels
    tiny-graphics
  )

target_include_directories(${TARGET_NAME}
  PRIVATE
    ${PROJECT_SOURCE_DIR}/lib
  )

add_subdirectory(wheels)
add_subdirectory(tiny-graphics)
