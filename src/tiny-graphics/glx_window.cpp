#include "glx_window.hpp"
#include <X11/Xlib.h>
#include "tiny-xlib/dispatcher.hpp"

namespace X11 {

GlxWindow::GlxWindow(::Display* dpy, Visual& visual, Size2 size, Pos2 pos)
    : Window(dpy, visual, std::move(size), std::move(pos)), 
      glx_ctx_(*this) {
  glx_ctx_.MakeCurrent(true);
}

}
