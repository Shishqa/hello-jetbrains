#include <iostream>
#include "dispatcher.hpp"
#include <X11/X.h>
#include <X11/Xlib.h>
#include "window.hpp"

namespace X11 {

EventDispatcher::EventDispatcher(::Display* dpy, long event_mask)
    : dpy_(dpy), event_mask_(event_mask) {
}

EventDispatcher::~EventDispatcher() {
  std::cerr << "destroying dispatcher\n";
}

void EventDispatcher::AddListener(Window* window) {
  XSelectInput(dpy_, window->Handle(), event_mask_);
  listeners_.insert(window);
}

void EventDispatcher::RemoveListener(Window* window) {
  garbage_.push(window);
}

long EventDispatcher::EventMask() const {
  return event_mask_;
}


void EventDispatcher::PollEvents() {
  XEvent event;
  do {
    XNextEvent(dpy_, &event);
    HandleEvent(event);
  } while (XPending(dpy_));
}


void EventDispatcher::CollectGarbage() {
  while (!garbage_.empty()) {
    auto listener = garbage_.front();
    garbage_.pop();
    listeners_.erase(listener);
  }
  if (listeners_.empty()) {
    Stop();
  }
}

void EventDispatcher::DisplayAll() {
  for (auto& listener : listeners_) {
    listener->OnExpose();
  }
}


void EventDispatcher::RunLoop() {
  if (listeners_.empty()) {
    return;
  }

  running_ = true;

  DisplayAll();
  while (running_) {
    std::cerr << "poll\n";
    PollEvents();
    std::cerr << "garbage_\n";
    CollectGarbage();
  }
}

void EventDispatcher::Stop() {
  running_ = false;
}

void EventDispatcher::HandleEvent(const XEvent& event) {
  for (auto& listener : listeners_) {
    SendEvent(listener, event);
  }
  if (event.type == Expose) {
    DisplayAll();
  }
}

void EventDispatcher::SendEvent(Window* listener, const XEvent& event) {
  switch (event.type) {
    case Expose:
      listener->OnDraw();
      need_expose_ = true;
      break;
    
    case ButtonPress:
      listener->OnMouseClicked(
          event.xbutton.button, 
          Pos2{event.xbutton.x, event.xbutton.y}
          );
      break;
    
    case ButtonRelease:
      listener->OnMouseClicked(
          event.xbutton.button, 
          Pos2{event.xbutton.x, event.xbutton.y}
          );
      break;
   
    case MotionNotify:
      listener->OnMouseMoved(
          Pos2{event.xmotion.x, event.xmotion.y}
          );
      break;

    case ClientMessage: {
      Atom atom = XInternAtom(dpy_, "WM_DELETE_WINDOW", False);
      if (event.xclient.data.l[0] == static_cast<long>(atom)) {
        std::cerr << "destroying\n";
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

}  // namespace X11
