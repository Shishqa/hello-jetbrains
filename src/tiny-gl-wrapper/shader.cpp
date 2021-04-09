#include "shader.hpp"
#include "gl_impl.hpp"

#include <iostream>
#include <stdexcept>

namespace GL {

Shader::Shader(uint32_t type, const char* source)
    : handle_(None) {
  handle_ = glCreateShader(type);
  glShaderSource(handle_, 1, &source, NULL);
  glCompileShader(handle_);

  int  success;
  char infoLog[512];
  glGetShaderiv(handle_, GL_COMPILE_STATUS, &success);
  if(!success) {
    glGetShaderInfoLog(handle_, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
  }
}

Shader::~Shader() {
}



}

