/*============================================================================*/
#ifndef _X11_GLX_CONTEXT_HPP
#define _X11_GLX_CONTEXT_HPP
/*============================================================================*/

#include <GL/glx.h>

/*============================================================================*/
namespace X11 {
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

class Window;

class GlxContext {
 public:
  GlxContext(Window& owner);

  ~GlxContext();

  GlxContext(const GlxContext& other) = delete;
  GlxContext& operator=(const GlxContext& other) = delete;

  void MakeCurrent(bool current);

  void Display();

 private:
  Window* owner_;
  GLXContext ctx_;
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
}  // namespace X11
/*============================================================================*/
#endif /* ifndef _X11_GLX_CONTEXT_HPP */
/*============================================================================*/
