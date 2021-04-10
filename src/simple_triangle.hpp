#ifndef _SIMPLE_TRIANGLE_HPP
#define _SIMPLE_TRIANGLE_HPP

#include <tiny-graphics/tiny_graphics.hpp>
#include "tiny-graphics/tiny-xlib/window.hpp"

namespace task {

class SimpleTriangle {
 public:
  SimpleTriangle();

  ~SimpleTriangle();

  void Draw();

  const Pos2& GetPos() const;

  void SetPos(Pos2 new_pos);

 private:  
  uint32_t vrtx_buff_;
  uint32_t vrtx_attr_;

  Pos2 pos_{0, 0};
};

}


#endif /* ifndef _SIMPLE_TRIANGLE_HPP */
