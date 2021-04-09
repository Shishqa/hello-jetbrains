/*============================================================================*/
#ifndef X_WRAPPER_WINDOW
#define X_WRAPPER_WINDOW
/*============================================================================*/

#include <X11/X.h>
#include <X11/Xlib.h>
#include <stdint.h>

#include <wheels/vector.hpp>
#include <wheels/util.hpp>

#include "display.hpp"
#include "dispatcher.hpp"
#include "visual.hpp"

using Size2 = wheels::Size2;
using Pos2 = wheels::Pos2;

/*============================================================================*/
namespace X11 {
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

class Window {
 public:
  Window(::Display* dpy, Visual& visual, Size2 size, Pos2 pos);

  Window() = delete;

  ~Window();

  ::Window Handle() const {
    return handle_;
  }
  
  ::Display* GetDisplay() const {
    return dpy_;
  }

  Visual* GetVisual() const {
    return visual_;
  }

  /* called when being destroyed */
  virtual void OnDestroy() {
  }

  virtual void OnDraw() {
  }

  virtual void OnExpose() {
  }

  virtual void OnMouseClicked(uint32_t button, const Pos2& where) {
    UNUSED(button);
    UNUSED(where); 
  }

  virtual void OnMouseReleased(uint32_t button, const Pos2& where) {
    UNUSED(button);
    UNUSED(where);
  }

  virtual void OnMouseMoved(const Pos2& where) {
    UNUSED(where);
  }

  virtual void OnEvent(const XEvent& event) {
    UNUSED(event);
  }

 private:
  void Destroy();

 private:
  ::Display* dpy_;
  Visual* visual_;
  ::Window handle_;
  Atom wm_delete_msg_;

  friend EventDispatcher;
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
}  // namespace X11
/*============================================================================*/
#endif /* ifndef X_WRAPPER_WINDOW */
/*============================================================================*/
