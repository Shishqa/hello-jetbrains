/*============================================================================*/
#ifndef DISPATCHER
#define DISPATCHER
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
  EventDispatcher(::Display* dpy, long event_mask = ExposureMask);

  ~EventDispatcher();

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
  Atom wm_delete_msg_;
  bool running_;
  bool need_expose_;
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
}  // namespace X11
/*============================================================================*/
#endif /* ifndef DISPATCHER */
/*============================================================================*/
