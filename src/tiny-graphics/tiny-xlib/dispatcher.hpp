/*============================================================================*/
#ifndef _X11_DISPATCHER_HPP
#define _X11_DISPATCHER_HPP
/*============================================================================*/

#include <unordered_set>
#include <queue>

#include <X11/X.h>
#include <X11/Xlib.h>

#include "display.hpp"

/*============================================================================*/
namespace X11 {
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

class Window;

class EventDispatcher {
 public:
  explicit EventDispatcher(::Display* dpy, long event_mask = ExposureMask);

  ~EventDispatcher();

  EventDispatcher(const EventDispatcher& other) = delete;
  EventDispatcher& operator=(const EventDispatcher& other) = delete;

  long EventMask() const;

  void AddListener(Window* window);

  void RemoveListener(Window* window);

  void RunLoop();

  void Stop();

 private:
  void PollEvents();

  void CollectGarbage();

  void DisplayAll();

  virtual void HandleEvent(const XEvent& event);

  virtual void SendEvent(Window* listener, const XEvent& event);

 private:
  ::Display* dpy_;
  long event_mask_;
  std::unordered_set<Window*> listeners_;
  std::unordered_set<Window*> pending_expose_;
  std::queue<Window*> garbage_;
  bool running_;
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
}  // namespace X11
/*============================================================================*/
#endif /* ifndef DISPATCHER */
/*============================================================================*/
