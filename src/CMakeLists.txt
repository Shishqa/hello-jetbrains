set(TARGET_NAME xlib-window)

add_executable(${TARGET_NAME}
    main.cpp
  )

target_link_libraries(${TARGET_NAME}
  PRIVATE
    wheels
    tiny-x-wrapper
  )

target_include_directories(${TARGET_NAME}
  PRIVATE
    ${PROJECT_SOURCE_DIR}/lib
  )


add_subdirectory(tiny-x-wrapper)
