#ifndef SHAPES
#define SHAPES

#include <GL/gl.h>
#include <wheels/vector.hpp>

using Vector2 = wheels::Vector2<double>;
using Point2 = wheels::Vector2<double>;

namespace X11 {

class Shape {
 public:
  explicit Shape(Point2 pos) {
    SetPos(std::move(pos));
  }

  void Translate(const Vector2& delta) {
    pos_ += delta;
  }

  void SetPos(Point2 pos) {
    pos_ = std::move(pos);
  }

  Point2 GetPos() const {
    return pos_;
  }

  virtual void Draw() const = 0;

 private:
  Point2 pos_; 
};

class Triangle : public Shape {
 public:
  explicit Triangle(Point2 dots[3]);

  virtual void Draw() const override {
    glBegin(GL_TRIANGLES);
     glVertex2f(dots_[0].x, dots_[0].y);
     glVertex2f(dots_[1].x, dots_[2].y);
     glVertex2f(dots_[2].x, dots_[2].y);
    glEnd();
  }

 private:
  Point2 dots_[3];
};

}


#endif /* ifndef SHAPES */
