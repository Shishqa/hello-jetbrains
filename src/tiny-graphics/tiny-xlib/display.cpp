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
#include <wheels/log.hpp>

#include "display.hpp"

/*============================================================================*/
namespace X11 {
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Display::Display(const char* name) {
  display_ = XOpenDisplay(name);
  if (!display_) {
    wheels::Log() << "cannot open display";
    throw std::runtime_error("X11: cannot open display");
  }
  wheels::Log() << "opened X connection " << display_;
}

Display::~Display() {
  XCloseDisplay(display_);
  wheels::Log() << "display " << display_ << " closed";
}

::Display* Display::Get() const {
  ASSERT(display_, "Display: bad display_");
  return display_;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
}  // namespace X11
/*============================================================================*/
