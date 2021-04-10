/*============================================================================*/

#include <stdexcept>

#include <X11/Xlib.h>
#include <GL/glx.h>

#include <wheels/log.hpp>

#include "visual.hpp"

/*============================================================================*/
namespace X11 {
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Visual::Visual(::Display* dpy) : vi_(nullptr), cmap_(None) {
  wheels::Log() << "initializing visual for display " << dpy;

  int screen = XDefaultScreen(dpy);

  int glx_major, glx_minor;
  if (!glXQueryVersion(dpy, &glx_major, &glx_minor) ||
      ((glx_major == 1) && (glx_minor < 3)) || (glx_major < 1)) {
    wheels::Log() << "Error: bad GLX version " << glx_major << "." << glx_minor;
    throw std::runtime_error("bad GLX version");
  }

  static constexpr int visual_attribs[] = {
    GLX_X_RENDERABLE,    True,
    GLX_DRAWABLE_TYPE,   GLX_WINDOW_BIT,
    GLX_RENDER_TYPE,     GLX_RGBA_BIT,
    GLX_X_VISUAL_TYPE,   GLX_TRUE_COLOR,
    GLX_RED_SIZE,        8,
    GLX_GREEN_SIZE,      8,
    GLX_BLUE_SIZE,       8,
    GLX_ALPHA_SIZE,      8,
    GLX_DEPTH_SIZE,      24,
    GLX_STENCIL_SIZE,    8,
    GLX_DOUBLEBUFFER,    True,
    None
  };

  int num_fbc = 0;
  GLXFBConfig* fbc = glXChooseFBConfig(dpy, screen, visual_attribs, &num_fbc);
  if (!fbc) {
    wheels::Log() << "Error: cannot find suitable framebuffer config";
    throw std::runtime_error("Cannot find framebuffer config");
  }

  framebuf_cfg_ = fbc[0];
  XFree(fbc);

  ctx_creator_ = reinterpret_cast<CtxCreator>(
      glXGetProcAddress((const GLubyte*)"glXCreateContextAttribsARB"));
  if (!ctx_creator_) {
    wheels::Log() << "Error: cannot find glXCreateContextAttribsARB()";
    throw std::runtime_error("glXCreateContextAttribsARB() not found");
  }

  vi_ = glXGetVisualFromFBConfig(dpy, framebuf_cfg_);
  if (!vi_) {
    wheels::Log() << "Error: cannot get visual from FB config";
    throw std::runtime_error("cannot get visual");
  }

  cmap_ =
      XCreateColormap(dpy, XRootWindow(dpy, screen), vi_->visual, AllocNone);
  if (!cmap_) {
    XFree(vi_);
    wheels::Log() << "Error: cannot create colormap";
    throw std::runtime_error("cannot create colormap");
  }

  wheels::Log() << "visual initialized";
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Visual::~Visual() {
  XFree(vi_);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

::GLXContext Visual::CreateGLXContext(::Display* dpy, const int* attr) const {
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
}  // namespace X11
/*============================================================================*/
