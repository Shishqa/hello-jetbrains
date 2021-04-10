/*============================================================================*/
#ifndef _SIMPLE_WINDOW_HPP
#define _SIMPLE_WINDOW_HPP
/*============================================================================*/

#include <stdint.h>
#include <tiny-graphics/tiny_graphics.hpp>
#include "simple_triangle.hpp"

/*============================================================================*/
namespace task {
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

class SimpleWindow : public tg::Window {
 public:
  SimpleWindow(::Display* dpy, X11::Visual& visual, Size2 size, Pos2 pos);

  void Draw() override;

  void OnMouseClicked(uint32_t button, const Pos2& where) override;

  void OnMouseReleased(uint32_t button, const Pos2& where) override;

  void OnMouseMoved(const Pos2& where) override;

 private:
  SimpleTriangle triangle_;
  bool is_active_{false};
  uint32_t offset_loc_;
  GL::Program main_program_;
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
}  // namespace task
/*============================================================================*/
#endif /* ifndef _SIMPLE_WINDOW_HPP */
/*============================================================================*/
