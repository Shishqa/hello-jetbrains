#include "tiny-opengl/gl_impl.hpp"
#include "window.hpp"

#include <wheels/log.hpp>

namespace tg {

Window::Window(::Display* dpy, X11::Visual& visual, Size2 size, Pos2 pos)
    : X11::Window(dpy, visual, std::move(size), std::move(pos)), 
      glx_ctx_(*this) {
  glx_ctx_.MakeCurrent(true);
  wheels::Log() << "GLX context bind to window " << this;
}

void Window::OnExpose() {
  const auto& attr = Attributes();
  glViewport(0, 0, attr.width, attr.height);
  Draw();
  glx_ctx_.Display();
}

}
