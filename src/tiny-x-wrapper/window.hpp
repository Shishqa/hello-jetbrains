/*============================================================================*/
#ifndef X_WRAPPER_WINDOW
#define X_WRAPPER_WINDOW
/*============================================================================*/

#include <X11/X.h>
#include <X11/Xlib.h>
#include <wheels/vector.hpp>

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

  virtual void OnExpose() {
  }

  virtual void OnClose() {
  }

 private:
  void Close();

  friend EventDispatcher;

 private:
  EventDispatcher* dispatcher_;
  XWindowAttributes attr_;
  ::Window id_;
  bool active_;
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
}  // namespace X11
/*============================================================================*/
#endif /* ifndef X_WRAPPER_WINDOW */
/*============================================================================*/
