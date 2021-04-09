set(TARGET_NAME tiny-xlib)

add_library(${TARGET_NAME})
target_sources(${TARGET_NAME}
  PUBLIC
    display.hpp
    visual.hpp
    dispatcher.hpp
    window.hpp
    shapes.hpp
  PRIVATE
    display.cpp
    visual.cpp
    dispatcher.cpp
    window.cpp
  )

target_link_libraries(${TARGET_NAME}
  PRIVATE
    wheels
    X11 ${X11_LIBRARIES}
  )

target_include_directories(${TARGET_NAME}
  PUBLIC
    ${PROJECT_SOURCE_DIR}/src/
    ${X11_INCLUDE_DIRECTORY}
  )
