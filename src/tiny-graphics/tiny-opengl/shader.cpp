/*============================================================================*/

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string_view>

#include <wheels/log.hpp>

#include "shader.hpp"
#include "gl_impl.hpp"

/*============================================================================*/
namespace GL {
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Shader::Shader(uint32_t type, std::string_view path) : handle_(None) {
  std::ifstream src_stream(path.data());
  if (!src_stream.is_open()) {
    wheels::Log() << "Error: cannot open shader at " << path;
    throw std::runtime_error("bad shader path");
  }

  std::stringstream source;
  source << src_stream.rdbuf();
  src_stream.close();

  handle_ = glCreateShader(type);
  Compile(source.str());

  wheels::Log() << "Shader " << handle_ << " loaded and compiled";
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Shader::Compile(std::string_view source) {
  const char* src_ptr = source.data();

  glShaderSource(handle_, 1, &src_ptr, NULL);
  glCompileShader(handle_);

  int status = 0;
  glGetShaderiv(handle_, GL_COMPILE_STATUS, &status);
  if (!status) {
    char info_log[512] = {};
    glGetShaderInfoLog(handle_, sizeof(info_log), NULL, info_log);
    wheels::Log() << "Error: cannot compile shader: " << info_log;
    throw std::runtime_error("cannot compile shader");
  }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Shader::~Shader() {
  glDeleteShader(handle_);
  wheels::Log() << "Shader " << handle_ << " deleted";
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
}  // namespace GL
/*============================================================================*/
