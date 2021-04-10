/*============================================================================*/

#include <cstdint>
#include <stdexcept>

#include <wheels/log.hpp>

#include "gl_impl.hpp"

/*============================================================================*/
namespace GL {
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Init() {
  wheels::Log() << "initializing OpenGL";
  if (glewInit() != GLEW_OK) {
    throw std::runtime_error("glew init");
  }

  const uint8_t* renderer = nullptr;
  renderer = glGetString(GL_RENDERER);
  wheels::Log() << "renderer: " << renderer;

  const uint8_t* version = nullptr;
  version = glGetString(GL_VERSION);
  wheels::Log() << "OpenGL version: " << version;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
}  // namespace GL
/*============================================================================*/

