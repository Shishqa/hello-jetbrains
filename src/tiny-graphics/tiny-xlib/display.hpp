/*============================================================================*/
#ifndef X11_WRAPPER_DISPLAY
#define X11_WRAPPER_DISPLAY 
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
#endif /* ifndef X11_WRAPPER_DISPLAY */
/*============================================================================*/
