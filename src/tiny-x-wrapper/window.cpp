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

Window::Window(EventDispatcher& dispatcher, Size2 size, Pos2 pos)
    : dispatcher_(&dispatcher), active_(true) {

  const Display* dpy = dispatcher_->GetDisplay();

  XSetWindowAttributes attr = {};
  attr.colormap = dpy->Colormap();
  attr.event_mask = dispatcher_->EventMask();

  id_ = XCreateWindow(
      dpy->Get(), 
      dpy->Root(), 
      pos.x, pos.y,
      size.x, size.y, 
      0, 
      dpy->VisualInfo()->depth, 
      InputOutput, 
      dpy->VisualInfo()->visual, 
      CWColormap | CWEventMask, 
      &attr);

  XMapWindow(dpy->Get(), id_);
  XStoreName(dpy->Get(), id_, "I <3 JetBrains");

  dispatcher_->AddListener(this);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Window::~Window() {
  std::cerr << "destroying window\n";
  Close();
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Window::Close() {
  if (!active_) {
    return;
  }
  active_ = false;

  OnClose();

  dispatcher_->RemoveListener(this);
  XDestroyWindow(dispatcher_->GetDisplay()->Get(), id_);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
}  // namespace X11
/*============================================================================*/
