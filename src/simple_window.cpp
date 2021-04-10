/*============================================================================*/

#include <tiny-graphics/tiny_graphics.hpp>
#include <wheels/util.hpp>

#include "simple_window.hpp"

/*============================================================================*/
namespace task {
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

SimpleWindow::SimpleWindow(::Display* dpy, X11::Visual& visual, tg::Size2 size,
                           tg::Pos2 pos)
    : tg::Window(dpy, visual, std::move(size), std::move(pos)) {
  GL::Shader vrtx_shader(GL_VERTEX_SHADER, "src/shaders/with_offset.vert");
  GL::Shader frag_shader(GL_FRAGMENT_SHADER, "src/shaders/standard.frag");
  main_program_.AttachShaders(vrtx_shader, frag_shader);
  main_program_.Link();

  offset_loc_ = glGetUniformLocation(main_program_.Handle(), "offset"); 
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void SimpleWindow::Draw() {
  const auto& attr = Attributes();

  GL::Color bg(0x25, 0x85, 0x4b, 255);
  glClearColor(UNPACK_COLOR(bg));
  glClear(GL_COLOR_BUFFER_BIT);

  if (is_active_) {
    main_program_.SetActive();

    glUniform2f(offset_loc_, 
                 2 * (float)triangle_.GetPos().x / (float)attr.width,
                -2 * (float)triangle_.GetPos().y / (float)attr.height);

    triangle_.Draw();
  }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void SimpleWindow::OnMouseClicked(uint32_t button, const tg::Pos2& where) {
  if (button == Button1) {
    is_active_ = true;
    triangle_.SetPos(where);
  }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void SimpleWindow::OnMouseReleased(uint32_t button, const tg::Pos2& where) {
  UNUSED(where);

  if (button == Button1) {
    is_active_ = false;
  }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void SimpleWindow::OnMouseMoved(const tg::Pos2& where) {
  if (is_active_) {
    triangle_.SetPos(where);
  }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
}  // namespace task
/*============================================================================*/

