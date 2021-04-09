#ifndef _GLX_CONTEXT_HPP
#define _GLX_CONTEXT_HPP

#include <GL/glx.h>
#include <X11/X.h>

namespace X11 {

class Window;

class GlxContext {
 public:
  GlxContext(Window& owner);

  ~GlxContext();

  void MakeCurrent(bool current);

  void Display();

 private:
  Window* owner_;
  GLXContext ctx_;
};

}

#endif /* ifndef _GLX_CONTEXT_HPP */
