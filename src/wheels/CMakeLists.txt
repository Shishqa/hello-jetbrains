set(TARGET_NAME wheels)
set(INCROOT ${CMAKE_CURRENT_SOURCE_DIR})

add_library(${TARGET_NAME})
target_sources(${TARGET_NAME}
  PUBLIC
    assert.hpp
    util.hpp
    vector.hpp
    log.hpp
  PRIVATE
    vector.ipp
    log.cpp
  )
