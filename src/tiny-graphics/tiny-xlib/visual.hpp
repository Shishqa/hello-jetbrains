/*============================================================================*/
#ifndef _X11_VISUAL_HPP
#define _X11_VISUAL_HPP
/*============================================================================*/

#include <X11/Xlib.h>
#include <GL/glx.h>

/*============================================================================*/
namespace X11 {
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

class Visual {
 public:
  explicit Visual(::Display* dpy);

  // Non-copyable
  Visual(const Visual& other) = delete;
  Visual& operator=(const Visual& other) = delete;

  ~Visual();

  const ::XVisualInfo* VisualInfo() const;

  ::Colormap Colormap() const;

  [[nodiscard]] ::GLXContext CreateGLXContext(::Display* dpy,
                                              const int* attr) const;

 private:
  using CtxCreator = GLXContext (*)(::Display*, GLXFBConfig, GLXContext, Bool,
                                    const int*);
  ::XVisualInfo* vi_;
  ::Colormap cmap_;
  CtxCreator ctx_creator_;
  GLXFBConfig framebuf_cfg_;
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
}  // namespace X11
/*============================================================================*/
#endif /* ifndef _X11_VISUAL_HPP */
/*============================================================================*/
