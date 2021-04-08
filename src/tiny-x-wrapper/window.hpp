/*============================================================================*/
#ifndef X_WRAPPER_WINDOW
#define X_WRAPPER_WINDOW
/*============================================================================*/

#include <X11/X.h>
#include <X11/Xlib.h>

#include <wheels/vector.hpp>
#include <wheels/util.hpp>

#include "display.hpp"
#include "dispatcher.hpp"

using Size2 = wheels::Size2;
using Pos2 = wheels::Pos2;

/*============================================================================*/
namespace X11 {
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

class Window {
 public:
  Window(EventDispatcher& dispatcher, Size2 size, Pos2 pos);

  Window() = delete;

  ~Window();

 protected:
  /* called when being destroyed */
  virtual void OnDestroy() {
  }

  virtual void OnExpose() {
  }

  virtual void OnMouseClicked(const Pos2& where) {
    UNUSED(where); 
  }

  virtual void OnMouseReleased(const Pos2& where) {
    UNUSED(where);
  }

  virtual void OnMouseMoved(const Pos2& where) {
    UNUSED(where);
  }

  virtual void OnKeyPressed(int key, const Pos2& where) {
    UNUSED(key);
    UNUSED(where);
  }

  virtual void OnKeyReleased(int key, const Pos2& where) {
    UNUSED(key);
    UNUSED(where);
  }

  virtual void OnEvent(const XEvent& event) {
    UNUSED(event);
  }

 private:
  void Destroy();

 private:
  EventDispatcher* dispatcher_;
  ::Window id_;
  Atom wm_delete_msg_;

  friend EventDispatcher;
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
}  // namespace X11
/*============================================================================*/
#endif /* ifndef X_WRAPPER_WINDOW */
/*============================================================================*/
