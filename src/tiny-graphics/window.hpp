#ifndef _GRAPHICS_WINDOW_H
#define _GRAPHICS_WINDOW_H 

#include "tiny-xlib/window.hpp"
#include "tiny-xlib/glx_context.hpp"

#include <iostream>

namespace tg {

class Window : public X11::Window {
 public: 
  Window(::Display* dpy, X11::Visual& visual, Size2 size, Pos2 pos);

  virtual void Draw() {
  }

 protected:
  void OnExpose() final;

 private:
  X11::GlxContext glx_ctx_;
};

}


#endif /* ifndef _GLX_WINDOW_H */
