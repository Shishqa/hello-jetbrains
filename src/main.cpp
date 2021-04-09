#include <iostream>

#include <cstdint>
#include <exception>

#include <X11/X.h>
#include <X11/Xlib.h>
#include <stdint.h>
#include <unistd.h>

#include "tiny-graphics/tiny-gl-wrapper/shader.hpp"
#include "tiny-graphics/tiny-gl-wrapper/gl_impl.hpp"
#include "tiny-graphics/tiny-gl-wrapper/program.hpp"
#include "tiny-graphics/tiny-x-wrapper/dispatcher.hpp"
#include "tiny-graphics/tiny-x-wrapper/display.hpp"
#include "tiny-graphics/glx_window.hpp"
#include "tiny-graphics/tiny-gl-wrapper/color.hpp"
#include "tiny-graphics/tiny-x-wrapper/shapes.hpp"
#include "tiny-graphics/tiny-x-wrapper/visual.hpp"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

class JBWindow : public X11::GlxWindow {
 public:
  JBWindow(::Display* dpy, X11::Visual& visual, Size2 size, Pos2 pos)
      : X11::GlxWindow(dpy, visual, std::move(size), std::move(pos)) {

     float vertices_[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
    };

    GL::Init();
    std::cerr << "init\n";

    GL::Shader vrtx_shader(GL_VERTEX_SHADER, 
    "#version 400 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0"
    );
  
    std::cerr << "2";

    GL::Shader frag_shader(GL_FRAGMENT_SHADER,
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0"
    );

    program = new GL::Program(vrtx_shader, frag_shader);

    std::cerr << "buffers\n";

    unsigned int VBO;
    glGenBuffers(1, &VBO); 

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_), vertices_, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
  }

  void OnDestroy() override {
    delete program;
  }

  void OnDraw() override {
    std::cerr << "expose\n";

    Color bg(255, 255, 255, 255);
    glClearColor(UNPACK_COLOR(bg));
    glClear(GL_COLOR_BUFFER_BIT);

    program->SetActive();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);


  }

 private:
  GL::Program* program;
  uint32_t VAO;

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

    dispatcher.RunLoop();

  } catch (const std::exception& ex) {
    std::cerr << "Exception: " << ex.what();
    return 1;
  } catch (...) {
    return 1;
  }

  return 0;
}
