#include <iostream>

#include <cstdint>
#include <exception>

#include <X11/X.h>
#include <X11/Xlib.h>
#include <unistd.h>

#include "tiny-gl-wrapper/shader.hpp"
#include "tiny-gl-wrapper/gl_impl.hpp"
#include "tiny-x-wrapper/dispatcher.hpp"
#include "tiny-x-wrapper/display.hpp"
#include "tiny-x-wrapper/glx_window.hpp"
#include "tiny-gl-wrapper/color.hpp"
#include "tiny-x-wrapper/shapes.hpp"
#include "tiny-x-wrapper/visual.hpp"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

class JBWindow : public X11::GlxWindow {
 public:
  JBWindow(::Display* dpy, X11::Visual& visual, Size2 size, Pos2 pos)
      : X11::GlxWindow(dpy, visual, std::move(size), std::move(pos)) {
  }

  void Draw() override {
    std::cerr << "expose\n";

    Color test(10, 100, 0, 255);
    glClearColor(UNPACK_COLOR(test));
    glClear(GL_COLOR_BUFFER_BIT);

    Color color(200, 0, 0, 255);
    glColor4f(UNPACK_COLOR(color));
    Point2 dots[3] = { {0,0}, {30, 0}, {0, 30} };
    X11::Triangle tr(dots);

    tr.Draw();
  }

 private:
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

int main(int /*argc*/, char* /*argv*/[]) {
  try {
    X11::Display display;
    X11::Visual visual(display.Get());

    X11::EventDispatcher dispatcher(display.Get(), 
        ExposureMask | ButtonMotionMask | ButtonPressMask | ButtonReleaseMask);

    JBWindow win(display.Get(), visual, Size2{500, 500}, Pos2{0, 0});

    dispatcher.AddListener(&win);

    GL::Init();

    GL::Shader shader(GL_VERTEX_SHADER, 
    "#version 400 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0");


    dispatcher.RunLoop();

  } catch (const std::exception& ex) {
    std::cerr << "Exception: " << ex.what();
    return 1;
  } catch (...) {
    return 1;
  }

  return 0;
}
