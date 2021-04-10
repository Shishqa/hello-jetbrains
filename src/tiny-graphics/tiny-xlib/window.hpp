/*============================================================================*/
#ifndef _X11_WINDOW_HPP
#define _X11_WINDOW_HPP
/*============================================================================*/

#include <cstdint>

#include <X11/Xlib.h>

#include <wheels/vector.hpp>
#include <wheels/util.hpp>

#include "display.hpp"
#include "dispatcher.hpp"
#include "visual.hpp"

/*============================================================================*/
namespace X11 {
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

using Size2 = wheels::Size2;
using Pos2 = wheels::Pos2;

class Window {
 public:
  Window(::Display* dpy, Visual& visual, Size2 size, Pos2 pos);

  Window() = delete;

  ~Window();

  Window(const Window& other) = delete;
  Window& operator=(const Window& other) = delete;

  ::Window Handle() const;
  
  ::Display* GetDisplay() const;

  Visual* GetVisual() const;

  const XWindowAttributes& Attributes() const;

  virtual void OnDestroy();

  virtual void OnExpose();

  virtual void OnMouseClicked(uint32_t button, const Pos2& where);

  virtual void OnMouseReleased(uint32_t button, const Pos2& where);

  virtual void OnMouseMoved(const Pos2& where);

  virtual void OnEvent(const XEvent& event);

 private:
  void Destroy();

 private:
  ::Display* dpy_;
  Visual* visual_;
  ::Window handle_;
  XWindowAttributes attr_;
  Atom wm_delete_msg_;

  friend EventDispatcher;
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
}  // namespace X11
/*============================================================================*/
#endif /* ifndef _X11_WINDOW_HPP */
/*============================================================================*/
