find_package(X11 REQUIRED)
if(!X11_FOUND) 
  message("X11 not found")
endif()
