#include "simple_triangle.hpp"
#include "tiny-graphics/tiny-xlib/window.hpp"

namespace task {

SimpleTriangle::SimpleTriangle() {
  static constexpr float vertices_[] = {
    -1.0f,  1.0f, 0.0f, 
    -0.5f,  1.0f, 0.0f,  
    -0.75f, 0.5f, 0.0f
  };

  glGenBuffers(1, &vrtx_buff_);

  glGenVertexArrays(1, &vrtx_attr_);
  glBindVertexArray(vrtx_attr_);

  glBindBuffer(GL_ARRAY_BUFFER, vrtx_buff_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_), vertices_, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
}

SimpleTriangle::~SimpleTriangle() {
  glDeleteBuffers(1, &vrtx_buff_);
  glDeleteVertexArrays(1, &vrtx_attr_);
}

void SimpleTriangle::Draw() {
  glBindVertexArray(vrtx_attr_);
  glDrawArrays(GL_TRIANGLES, 0, 3);
}

const Pos2& SimpleTriangle::GetPos() const {
  return pos_;
}

void SimpleTriangle::SetPos(Pos2 new_pos) {
  pos_ = std::move(new_pos);
}

}
