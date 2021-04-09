/*============================================================================*/

#include <X11/X.h>
#include <X11/Xlib.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glx.h>
#include <X11/Xutil.h>

#include <iostream>
#include <stdexcept>

#include <wheels/assert.hpp>

#include "display.hpp"

/*============================================================================*/
namespace X11 {
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Display::Display(const char* name) {
  display_ = XOpenDisplay(name);
  if (!display_) {
    throw std::runtime_error("X11: cannot open display");
  }
}

Display::~Display() {
  std::cerr << "closing display\n";
  XCloseDisplay(display_);
}

::Display* Display::Get() const {
  return display_;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
}  // namespace X11
/*============================================================================*/
