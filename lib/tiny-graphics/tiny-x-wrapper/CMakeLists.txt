set(TARGET_NAME tiny-x-wrapper)
set(INCROOT ${PROJECT_SOURCE_DIR}/lib/tiny-graphics/tiny-x-wrapper)

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
  PRIVATE
    ${INCROOT}
    ${PROJECT_SOURCE_DIR}/lib/
  PUBLIC
    ${X11_INCLUDE_DIRECTORY}
  )
