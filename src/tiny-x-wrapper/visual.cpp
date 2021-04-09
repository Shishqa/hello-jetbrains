#include "visual.hpp"
#include <X11/X.h>
#include <X11/Xlib.h>

#include <GL/gl.h>
#include <GL/glx.h>
#include <X11/Xutil.h>
#include <stdexcept>

namespace X11 {

Visual::Visual(::Display* dpy)
    : vi_(nullptr), cmap_(None) {

  int screen = XDefaultScreen(dpy);
 
  int glx_major, glx_minor;
  // FBConfigs were added in GLX version 1.3.
  if ( !glXQueryVersion( dpy, &glx_major, &glx_minor ) || 
       ( ( glx_major == 1 ) && ( glx_minor < 3 ) ) || ( glx_major < 1 ) )
  {
    throw std::runtime_error("bad glx version");
  }

  static int visual_attribs[] = {
    GLX_X_RENDERABLE    , True,
    GLX_DRAWABLE_TYPE   , GLX_WINDOW_BIT,
    GLX_RENDER_TYPE     , GLX_RGBA_BIT,
    GLX_X_VISUAL_TYPE   , GLX_TRUE_COLOR,
    GLX_RED_SIZE        , 8,
    GLX_GREEN_SIZE      , 8,
    GLX_BLUE_SIZE       , 8,
    GLX_ALPHA_SIZE      , 8,
    GLX_DEPTH_SIZE      , 24,
    GLX_STENCIL_SIZE    , 8,
    GLX_DOUBLEBUFFER    , True,
    None
  };

  int num_fbc = 0;
  GLXFBConfig *fbc = glXChooseFBConfig(dpy, screen, visual_attribs, &num_fbc);
  if (!fbc) {
    throw std::runtime_error("Cannot find framebuffer config");
  }

  framebuf_cfg_ = fbc[0];
  XFree(fbc);

  ctx_creator_ = reinterpret_cast<CtxCreator>(
    glXGetProcAddress((const GLubyte*)"glXCreateContextAttribsARB"));
  if (!ctx_creator_) {
    throw std::runtime_error("glXCreateContextAttribsARB() not found");
  }

  vi_ = glXGetVisualFromFBConfig(dpy, framebuf_cfg_);
  if (!vi_) {
    throw std::runtime_error("no visual");
  }

  cmap_ = XCreateColormap(dpy, XRootWindow(dpy, screen), 
                          vi_->visual, AllocNone);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Visual::~Visual() {
  XFree(vi_);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

::GLXContext Visual::CreateGLXContext(::Display *dpy, const int *attr) const {
  return ctx_creator_(dpy, framebuf_cfg_, nullptr, true, attr);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

const ::XVisualInfo* Visual::VisualInfo() const {
  return vi_;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

::Colormap Visual::Colormap() const {
  return cmap_;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
}  // namespace
/*============================================================================*/
