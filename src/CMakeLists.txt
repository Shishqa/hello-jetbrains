set(TARGET_NAME hello-jetbrains)

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

add_subdirectory(wheels)
add_subdirectory(tiny-graphics)
