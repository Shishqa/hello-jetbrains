#include <iostream>

#include <exception>

#include <wheels/log.hpp>
#include "simple_window.hpp"

int main(int /*argc*/, char* /*argv*/[]) {
  try {
    wheels::log::Init("application.log");

    X11::Display display;
    X11::Visual visual(display.Get());

    {
      tg::Window dummy(display.Get(), visual, Size2{100, 100}, Pos2{});
      GL::Init();
    }

    X11::EventDispatcher dispatcher(display.Get(), 
        ExposureMask | PointerMotionMask | ButtonPressMask | ButtonReleaseMask | StructureNotifyMask);

    task::SimpleWindow win(display.Get(), visual, Size2{500, 500}, Pos2{0, 0});
    dispatcher.AddListener(&win);

    dispatcher.RunLoop();

  } catch (const std::exception& ex) {
    std::cerr << "Caught exception: " << ex.what();
    return 1;
  } catch (...) {
    return 1;
  }

  return 0;
}
