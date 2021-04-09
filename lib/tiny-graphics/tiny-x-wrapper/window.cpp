/*============================================================================*/

#include <iostream>

#include <GL/glx.h>
#include <X11/X.h>
#include <X11/Xlib.h>
#include <cstddef>
#include <stdexcept>

#include "dispatcher.hpp"
#include "display.hpp"
#include "window.hpp"

/*============================================================================*/
namespace X11 {
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Window::Window(::Display* dpy, Visual& visual, Size2 size, Pos2 pos)
    : dpy_(dpy), visual_(&visual) {

  XSetWindowAttributes attr = {};
  attr.colormap = visual.Colormap();

  handle_ = XCreateWindow(
      dpy_, 
      XRootWindow(dpy_, XDefaultScreen(dpy_)), 
      pos.x, pos.y,
      size.x, size.y, 
      0, 
      visual.VisualInfo()->depth, 
      InputOutput, 
      visual.VisualInfo()->visual, 
      CWColormap, &attr);

  XMapWindow(dpy, handle_);

  wm_delete_msg_ = XInternAtom(dpy, "WM_DELETE_WINDOW", false);
	XSetWMProtocols(dpy, handle_, &wm_delete_msg_, 1);

  std::cerr << "window created\n";
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Window::~Window() {
  std::cerr << "destroying window\n";
  Destroy();
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Window::Destroy() {
  if (None == handle_) {
    return;
  }

  OnDestroy();

  XDestroyWindow(dpy_, handle_);
  handle_ = None;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
}  // namespace X11
/*============================================================================*/
