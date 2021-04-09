#ifndef _GLX_WINDOW_H
#define _GLX_WINDOW_H 

#include <X11/Xlib.h>
#include "window.hpp"
#include "glx_context.hpp"

namespace X11 {

class GlxWindow : public Window {
 public: 
  GlxWindow(::Display* dpy, Visual& visual, Size2 size, Pos2 pos);

 protected:
  void OnExpose() final {
    glx_ctx_.Display();
  }

 protected:
  GlxContext glx_ctx_;
};

}


#endif /* ifndef _GLX_WINDOW_H */
