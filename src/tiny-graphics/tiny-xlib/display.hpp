/*============================================================================*/
#ifndef _X11_DISPLAY_HPP
#define _X11_DISPLAY_HPP 
/*============================================================================*/

#include <X11/Xlib.h>
 
/*============================================================================*/
namespace X11 {
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

class Display {
 public:
  Display(const char* name = nullptr);

  ~Display();

  // Non-copyable
  Display(const Display& other) = delete;
  Display& operator=(const Display& other) = delete;

  ::Display* Get() const;

 private:
  void Open();

  void Close();

 private:
  ::Display* display_;
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
}  // namespace X11
/*============================================================================*/
#endif /* ifndef _X11_DISPLAY_HPP */
/*============================================================================*/
