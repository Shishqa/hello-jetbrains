/*============================================================================*/
#ifndef X11_WRAPPER_DISPLAY
#define X11_WRAPPER_DISPLAY 
/*============================================================================*/

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
 
/*============================================================================*/
namespace X11 {
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

class Display {
 public:
  Display();

  ~Display();

  // Non-copyable
  Display(const Display& other) = delete;
  Display& operator=(const Display& other) = delete;

  ::Display* Get() const;

  ::Window Root() const;

  int Screen() const;

  ::XVisualInfo* VisualInfo() const;

  ::Colormap Colormap() const;

 private:
  void Open();

  void Close();

 private:
  ::Display* display_;
  ::XVisualInfo* vi_;
  ::Colormap cmap_;
  ::Window root_window_;
  int screen_;
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
}  // namespace X11
/*============================================================================*/
#endif /* ifndef X11_WRAPPER_DISPLAY */
/*============================================================================*/
