#include <iostream>
#include "dispatcher.hpp"
#include <X11/X.h>
#include <X11/Xlib.h>
#include "window.hpp"

namespace X11 {

EventDispatcher::EventDispatcher(const Display& dpy, long event_mask)
    : dpy_(&dpy), event_mask_(event_mask) {
  wm_delete_msg_ = XInternAtom(dpy_->Get(), "WM_DELETE_WINDOW", True);
}

EventDispatcher::EventDispatcher(const Display& dpy)
    : EventDispatcher(dpy, ExposureMask) {
}

EventDispatcher::~EventDispatcher() {
  std::cerr << "destroying dispatcher\n";
}

void EventDispatcher::AddListener(Window* window) {
  listeners_.insert(window);
  XSetWMProtocols(dpy_->Get(), window->id_, &wm_delete_msg_, 1);
}

void EventDispatcher::RemoveListener(Window* window) {
  garbage_.insert(window);
}

const Display* EventDispatcher::GetDisplay() const {
  return dpy_;
}

long EventDispatcher::EventMask() const {
  return event_mask_;
}

void EventDispatcher::RunLoop() {
  if (listeners_.empty()) {
    return;
  }

  running_ = true;

  XEvent event;
  while (running_) {
    do {
      XNextEvent(dpy_->Get(), &event);
      HandleEvent(event);
    } while (XPending(dpy_->Get()));

    for (auto& win : garbage_) {
      listeners_.erase(win);
    }
    garbage_.clear();

    if (listeners_.empty()) {
      Stop();
    }
  }
}

void EventDispatcher::Stop() {
  running_ = false;
}

void EventDispatcher::HandleEvent(const XEvent& event) {
  for (auto& listener : listeners_) {
    SendEvent(listener, event);
  }
}

void EventDispatcher::SendEvent(Window* listener, const XEvent& event) {
  switch (event.type) {
    case Expose:
      listener->OnExpose();
      break;
    case ClientMessage:
      if (event.xclient.data.l[0] == static_cast<long>(wm_delete_msg_)) {
        listener->Close();         
      }
    default:
      break;
  }
}

}  // namespace X11
