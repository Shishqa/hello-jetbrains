#ifndef _VISUAL_HPP
#define _VISUAL_HPP

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include <GL/glx.h>

namespace X11 {

class Visual {
 public:
  Visual(::Display* dpy);

  // Non-copyable
  Visual(const Visual& other) = delete;
  Visual& operator=(const Visual& other) = delete;

  ~Visual();

  const ::XVisualInfo* VisualInfo() const;

  ::Colormap Colormap() const;
  
  ::GLXContext CreateGLXContext(::Display* dpy, const int* attr) const;

 private:
  using CtxCreator = GLXContext (*)(::Display*, GLXFBConfig, GLXContext, Bool,
                                    const int*);
  ::XVisualInfo* vi_;
  ::Colormap cmap_;
  CtxCreator ctx_creator_;
  GLXFBConfig framebuf_cfg_;
};

}  // namespace X11

#endif /* ifndef _VISUAL_HPP */
