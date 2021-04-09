#ifndef _PROGRAM_HPP
#define _PROGRAM_HPP

#include <stdexcept>
#include <utility>
#include <cstdint>
#include "gl_impl.hpp"
#include "shader.hpp"

namespace GL {

class Program {
 public:
  Program() = delete;

  template <typename... Shaders>
  Program(Shaders&&... shaders) {
    handle_ = glCreateProgram(); 
    AttachShaders(std::forward<Shaders>(shaders)...);
    glLinkProgram(handle_);

    int success = 0;
    glGetProgramiv(handle_, GL_LINK_STATUS, &success);
    if(!success) {
      throw std::runtime_error("bad program");
    }
  }

  ~Program() = default;

  void SetActive() {
    glUseProgram(handle_);
  }

 private:
  template <typename... Shaders>
  void AttachShaders(const Shader& shader, Shaders&&... shaders) {
    Attach(shader);
    AttachShaders(std::forward<Shaders>(shaders)...);
  }

  void AttachShaders(const Shader& shader) {
    Attach(shader);
  }

  void Attach(const Shader& shader) {
    glAttachShader(handle_, shader.Handle());
  }

  uint32_t handle_;
};

}

#endif /* ifndef _PROGRAM_HPP */
