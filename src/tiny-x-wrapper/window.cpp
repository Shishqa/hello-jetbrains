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
    : dispatcher_(&dispatcher) {

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

  wm_delete_msg_ = XInternAtom(dpy->Get(), "WM_DELETE_WINDOW", false);
	XSetWMProtocols(dpy->Get(), id_, &wm_delete_msg_, 1);

  dispatcher_->AddListener(this);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Window::~Window() {
  std::cerr << "destroying window\n";
  Destroy();
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Window::Destroy() {
  if (None == id_) {
    return;
  }

  OnDestroy();

  dispatcher_->RemoveListener(this);

  XClearWindow(dispatcher_->GetDisplay()->Get(), id_);
  XDestroyWindow(dispatcher_->GetDisplay()->Get(), id_);
  id_ = None;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

const Display* Window::GetDisplay() {
  return dispatcher_->GetDisplay();
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
}  // namespace X11
/*============================================================================*/
