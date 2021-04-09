#include "glx_context.hpp"
#include <GL/glx.h>
#include <X11/X.h>
#include <stdexcept>
#include "visual.hpp"
#include "window.hpp"
#include <iostream>

namespace X11 {

GlxContext::GlxContext(Window& owner)
    : owner_(&owner) {

  static int context_attribs[] = {
    GLX_CONTEXT_MAJOR_VERSION_ARB, 4,
    GLX_CONTEXT_MINOR_VERSION_ARB, 2,
    None
  };

  ctx_ = owner_->GetVisual()->CreateGLXContext(
      owner_->GetDisplay(), context_attribs);
  if (!ctx_) {
    throw std::runtime_error("cannot create context");
  }

  std::cerr << "glx_context created\n";
}

GlxContext::~GlxContext() {
  MakeCurrent(false);
  glXDestroyContext(owner_->GetDisplay(), ctx_); 
}

void GlxContext::MakeCurrent(bool current) {
  if (current) {
    glXMakeCurrent(owner_->GetDisplay(), owner_->Handle(), ctx_);
  } else {
    glXMakeCurrent(owner_->GetDisplay(), None, nullptr);
  }
}

void GlxContext::Display() {
  MakeCurrent(true);
  glXSwapBuffers(owner_->GetDisplay(), owner_->Handle());
}

}
