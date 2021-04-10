/*============================================================================*/
#ifndef _TINY_GRAPHICS_WINDOW_HPP
#define _TINY_GRAPHICS_WINDOW_HPP
/*============================================================================*/

#include <tiny-graphics/tiny-xlib/window.hpp>
#include <tiny-graphics/tiny-xlib/glx_context.hpp>

/*============================================================================*/
namespace tg {
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

using Size2 = X11::Size2;
using Pos2 = X11::Pos2;

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

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
}  // namespace tg
/*============================================================================*/
#endif /* ifndef _TINY_GRAPHICS_WINDOW_HPP */
/*============================================================================*/
