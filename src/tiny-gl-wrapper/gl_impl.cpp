#include "gl_impl.hpp"

#include <stdexcept>

namespace GL {

void Init() {
  if (glewInit() != GLEW_OK) {
    throw std::runtime_error("glew init");
  }
}

}
