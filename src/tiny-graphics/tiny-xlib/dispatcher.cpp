/*============================================================================*/

#include <X11/X.h>
#include <X11/Xlib.h>

#include <wheels/log.hpp>

#include "dispatcher.hpp"
#include "window.hpp"

/*============================================================================*/
namespace X11 {
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

EventDispatcher::EventDispatcher(::Display* dpy, long event_mask)
    : dpy_(dpy), event_mask_(event_mask), running_(false) {
  wheels::Log() << "created event dispatcher " << this;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

EventDispatcher::~EventDispatcher() {
  wheels::Log() << "destroying event dispatcher " << this;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void EventDispatcher::AddListener(Window* window) {
  XSelectInput(dpy_, window->Handle(), event_mask_);
  listeners_.insert(window);
  wheels::Log() << "added listener " << window << " to dispatcher " << this;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void EventDispatcher::RemoveListener(Window* window) {
  garbage_.push(window);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

long EventDispatcher::EventMask() const {
  return event_mask_;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void EventDispatcher::PollEvents() {
  XEvent event;
  do {
    XNextEvent(dpy_, &event);
    HandleEvent(event);
  } while (XPending(dpy_));
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void EventDispatcher::CollectGarbage() {
  while (!garbage_.empty()) {
    auto listener = garbage_.front();
    garbage_.pop();
    listeners_.erase(listener);
    wheels::Log() << "removed listener " << listener << " from dispatcher "
                  << this;
  }
  if (listeners_.empty()) {
    wheels::Log() << "dispatcher(" << this
                  << ") stopping as there is no listeners";
    Stop();
  }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void EventDispatcher::DisplayAll() {
  for (auto& listener : listeners_) {
    listener->OnExpose();
  }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void EventDispatcher::RunLoop() {
  if (listeners_.empty()) {
    return;
  }

  wheels::Log() << "running dispatcher(" << this << ")";
  running_ = true;

  while (running_) {
    DisplayAll();
    PollEvents();
    CollectGarbage();
  }

  wheels::Log() << "stopping dispatcher(" << this << ")";
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void EventDispatcher::Stop() {
  running_ = false;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void EventDispatcher::HandleEvent(const XEvent& event) {
  for (auto& listener : listeners_) {
    SendEvent(listener, event);
  }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void EventDispatcher::SendEvent(Window* listener, const XEvent& event) {
  switch (event.type) {
    case ButtonPress:
      listener->OnMouseClicked(event.xbutton.button,
                               Pos2{event.xbutton.x, event.xbutton.y});
      break;

    case ButtonRelease:
      listener->OnMouseReleased(event.xbutton.button,
                                Pos2{event.xbutton.x, event.xbutton.y});
      break;

    case MotionNotify:
      listener->OnMouseMoved(Pos2{event.xmotion.x, event.xmotion.y});
      break;

    case ClientMessage: {
      Atom delete_msg = XInternAtom(dpy_, "WM_DELETE_WINDOW", False);
      if (event.xclient.data.l[0] == static_cast<long>(delete_msg)) {
        wheels::Log() << "got message from the WM, destroying " << listener;
        RemoveListener(listener);
        listener->Destroy();
      }
      break;
    }

    default:
      listener->OnEvent(event);
      break;
  }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
}  // namespace X11
/*============================================================================*/
