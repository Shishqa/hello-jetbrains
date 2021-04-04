/*============================================================================*/
#ifndef DISPATCHER
#define DISPATCHER
/*============================================================================*/

#include <unordered_set>

#include <X11/X.h>
#include <X11/Xlib.h>

#include "display.hpp"

/*============================================================================*/
namespace X11 {
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

class Window;

class EventDispatcher {
 public:
  EventDispatcher(const Display& dpy, long event_mask);
  
  explicit EventDispatcher(const Display& dpy);

  ~EventDispatcher();

  const Display* GetDisplay() const;

  long EventMask() const;

  void AddListener(Window* window);
  
  void RemoveListener(Window* window);

  void RunLoop();

  void Stop();

 private: 
  virtual void HandleEvent(const XEvent& event);

  virtual void SendEvent(Window* listener, const XEvent& event);

 private:
  const Display* dpy_;
  long event_mask_;
  std::unordered_set<Window*> listeners_;
  std::unordered_set<Window*> garbage_;
  Atom wm_delete_msg_;
  bool running_;
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
}  // namespace X11
/*============================================================================*/
#endif /* ifndef DISPATCHER */
/*============================================================================*/
