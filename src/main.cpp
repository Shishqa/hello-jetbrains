#include <iostream>

#include <cstdint>
#include <exception>

#include <X11/X.h>
#include <X11/Xlib.h>
#include <unistd.h>

#include "tiny-x-wrapper/dispatcher.hpp"
#include "tiny-x-wrapper/display.hpp"
#include "tiny-x-wrapper/window.hpp"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

class JBWindow : public X11::Window {
 public:
  JBWindow(X11::EventDispatcher& dispatcher, Size2 size, Pos2 pos)
      : X11::Window(dispatcher, size, pos) {
  }

  void OnExpose() override {
    std::cout << "JBWindow :: Expose!\n";
  }
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

int main(int /*argc*/, char* /*argv*/[]) {
  try {
    X11::Display display;
    X11::EventDispatcher dispatcher(display);

    JBWindow win(dispatcher, Size2{500, 500}, Pos2{0, 0});

    dispatcher.RunLoop();

  } catch (const std::exception& ex) {
    std::cerr << "Exception: " << ex.what();
    return 1;
  } catch (...) {
    return 1;
  }

  return 0;
}
