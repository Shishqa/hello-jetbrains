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

void Display::Open() {
  display_ = XOpenDisplay(nullptr);
  if (!display_) {
    throw std::runtime_error("X11: cannot connect to X server");
  }
}

void Display::Close() {
  XCloseDisplay(display_);
  display_ = nullptr;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Display::Display() {
  Open();

  screen_ = XDefaultScreen(display_);
  root_window_ = XDefaultRootWindow(display_);

  if (!glXQueryExtension(display_, nullptr, nullptr)) {
    throw std::runtime_error("no GLX");
  }

  GLint attr[] = {GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None};

  vi_ = glXChooseVisual(display_, screen_, attr);
  if (!vi_) {
    throw std::runtime_error("no visual");
  }

  cmap_ = XCreateColormap(display_, root_window_, vi_->visual, AllocNone);
}

Display::~Display() {
  std::cerr << "destroying display\n";
  free(vi_);
  Close();
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

::Display* Display::Get() const {
  return display_;
}

::Window Display::Root() const {
  return root_window_;
}

int Display::Screen() const {
  return screen_;
}

::XVisualInfo* Display::VisualInfo() const {
  return vi_;
}

::Colormap Display::Colormap() const {
  return cmap_;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
}  // namespace X11
/*============================================================================*/
