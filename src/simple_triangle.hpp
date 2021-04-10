/*============================================================================*/
#ifndef _SIMPLE_TRIANGLE_HPP
#define _SIMPLE_TRIANGLE_HPP
/*============================================================================*/

#include <tiny-graphics/tiny_graphics.hpp>

/*============================================================================*/
namespace task {
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

class SimpleTriangle {
 public:
  SimpleTriangle();

  ~SimpleTriangle();

  void Draw();

  const tg::Pos2& GetPos() const;

  void SetPos(tg::Pos2 new_pos);

 private:  
  uint32_t vrtx_buff_;
  uint32_t vrtx_attr_;
  tg::Pos2 pos_{0, 0};
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
}  // namespace task
/*============================================================================*/
#endif /* ifndef _SIMPLE_TRIANGLE_HPP */
/*============================================================================*/

