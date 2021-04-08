#ifndef GRAPHIC_WINDOW
#define GRAPHIC_WINDOW

#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>

#include <X11/Xlib.h>
#include "dispatcher.hpp"
#include "window.hpp"
#include <stdexcept>
#include <iostream>

namespace X11 {

class GraphicWindow : public Window {
 public:
  GraphicWindow(EventDispatcher& dispatcher, Size2 size, Pos2 pos)
      : Window(dispatcher, size, pos) {
    graph_ctx_ = glXCreateNContext(GetDisplay()->Get(),
                                  GetDisplay()->VisualInfo(), None, True);
    // if (!graph_ctx_) {
    //  throw std::runtime_error("could not create rendering context");
    //}

    // glXMakeCurrent(GetDisplay()->Get(), Id(), graph_ctx_);
  }

  void OnDestroy() {
    std::cerr << "destroying graphic ctx\n";
    // glXDestroyContext(GetDisplay()->Get(), graph_ctx_);
  }

  void OnExpose() final {
    // XWindowAttributes attr;
    // XGetWindowAttributes(GetDisplay()->Get(), Id(), &attr);

    // glViewport(0, 0, attr.width, attr.height);
    // OnDraw();
    // glXSwapBuffers(GetDisplay()->Get(), Id());
  }

  virtual void OnDraw() {
  }

 protected:
  GLXContext graph_ctx_;
};

}  // namespace X11

#endif /* ifndef GRAPHIC_WINDOW */
