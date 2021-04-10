/*============================================================================*/
#ifndef _SIMPLE_WINDOW_HPP
#define _SIMPLE_WINDOW_HPP
/*============================================================================*/

#include <cstdint>
#include <tiny-graphics/tiny_graphics.hpp>

#include "simple_triangle.hpp"

/*============================================================================*/
namespace task {
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

class SimpleWindow : public tg::Window {
 public:
  SimpleWindow(::Display* dpy, X11::Visual& visual, tg::Size2 size, tg::Pos2 pos);

  void Draw() override;

  void OnMouseClicked(uint32_t button, const tg::Pos2& where) override;

  void OnMouseReleased(uint32_t button, const tg::Pos2& where) override;

  void OnMouseMoved(const tg::Pos2& where) override;

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
