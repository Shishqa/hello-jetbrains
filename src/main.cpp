/*============================================================================*/

#include <iostream>
#include <exception>
#include <wheels/log.hpp>

#include "simple_window.hpp"

/*============================================================================*/

int main(int /*argc*/, char* /*argv*/[]) {
  try {
    wheels::log::Init("application.log");

    X11::Display display;
    X11::Visual visual(display.Get());

    {
      // dummy is needed to initialize OpenGL properly
      // https://community.khronos.org/t/help-solve-glew-failure-with-glx/63190/2
      tg::Window dummy(display.Get(), visual, tg::Size2{100, 100}, tg::Pos2{});
      GL::Init();
    }

    X11::EventDispatcher dispatcher(
        display.Get(), ExposureMask | PointerMotionMask | ButtonPressMask |
                           ButtonReleaseMask | StructureNotifyMask);

    task::SimpleWindow win(display.Get(), visual, tg::Size2{500, 500},
                           tg::Pos2{0, 0});
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

/*============================================================================*/
