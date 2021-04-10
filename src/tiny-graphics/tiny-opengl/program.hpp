#ifndef _PROGRAM_HPP
#define _PROGRAM_HPP

#include <stdint.h>
#include <stdexcept>
#include <utility>
#include <cstdint>
#include <unordered_set>

#include "gl_impl.hpp"
#include "shader.hpp"

namespace GL {

class Program {
 public:
  Program();

  ~Program();

  Program(const Program& other) = delete;
  Program& operator=(const Program& other) = delete;

  uint32_t Handle() const {
    return handle_;
  }

  template <typename... Shaders>
  void AttachShaders(const Shader& shader, Shaders&&... shaders) {
    Attach(shader);
    AttachShaders(std::forward<Shaders>(shaders)...);
  }

  void AttachShaders(const Shader& shader) {
    Attach(shader);
  }

  void Link();

  void SetActive() {
    glUseProgram(handle_);
  }

 private:
  void Attach(const Shader& shader);

  uint32_t handle_;
  std::unordered_set<uint32_t> shaders_;
};

}

#endif /* ifndef _PROGRAM_HPP */
