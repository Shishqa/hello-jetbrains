set(TARGET_NAME wheels)
set(INCROOT ${CMAKE_CURRENT_SOURCE_DIR})

add_library(${TARGET_NAME}
  INTERFACE
    assert.hpp
    util.hpp
    vector.hpp
    vector.ipp
  )
