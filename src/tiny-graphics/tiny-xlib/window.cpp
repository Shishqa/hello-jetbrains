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

#include <wheels/log.hpp>

/*============================================================================*/
namespace X11 {
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Window::Window(::Display* dpy, Visual& visual, Size2 size, Pos2 pos)
    : dpy_(dpy), visual_(&visual) {
  XSetWindowAttributes attr = {};
  attr.colormap = visual.Colormap();

  handle_ =
      XCreateWindow(dpy_, XRootWindow(dpy_, XDefaultScreen(dpy_)), pos.x, pos.y,
                    size.x, size.y, 0, visual.VisualInfo()->depth, InputOutput,
                    visual.VisualInfo()->visual, CWColormap, &attr);

  XMapWindow(dpy, handle_);

  wm_delete_msg_ = XInternAtom(dpy, "WM_DELETE_WINDOW", false);
  XSetWMProtocols(dpy, handle_, &wm_delete_msg_, 1);

  XGetWindowAttributes(dpy_, handle_, &attr_);

  wheels::Log() << "window " << this << " created";
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Window::~Window() {
  Destroy();
  wheels::Log() << "window " << this << " destroyed (in destructor)";
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Window::Destroy() {
  if (None == handle_) {
    return;
  }

  OnDestroy();

  XDestroyWindow(dpy_, handle_);
  handle_ = None;

  wheels::Log() << "window " << this << " destroyed (in Destroy())";
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

::Window Window::Handle() const {
  return handle_;
}

::Display* Window::GetDisplay() const {
  return dpy_;
}

Visual* Window::GetVisual() const {
  return visual_;
}

const XWindowAttributes& Window::Attributes() const {
  return attr_;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Window::OnDestroy() {
}

void Window::OnExpose() {
}

void Window::OnMouseClicked(uint32_t button, const Pos2& where) {
  UNUSED(button);
  UNUSED(where);
}

void Window::OnMouseReleased(uint32_t button, const Pos2& where) {
  UNUSED(button);
  UNUSED(where);
}

void Window::OnMouseMoved(const Pos2& where) {
  UNUSED(where);
}

void Window::OnEvent(const XEvent& event) {
  if (event.type == ConfigureNotify) {
    XGetWindowAttributes(dpy_, handle_, &attr_);
  }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
}  // namespace X11
/*============================================================================*/
