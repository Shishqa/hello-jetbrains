/*============================================================================*/

#include <wheels/log.hpp>

#include "program.hpp"
#include "shader.hpp"

/*============================================================================*/
namespace GL {
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Program::Program() {
  handle_ = glCreateProgram();
  wheels::Log() << "Program " << handle_ << " created";
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Program::~Program() {
  glDeleteProgram(handle_);
  wheels::Log() << "Program " << handle_ << " deleted";
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Program::Attach(const Shader& shader) {
  glAttachShader(handle_, shader.Handle());
  shaders_.insert(shader.Handle());
  wheels::Log() << "Attached shader " << shader.Handle() << " to the program "
                << handle_;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Program::Link() {
  glLinkProgram(handle_);

  int success = 0;
  glGetProgramiv(handle_, GL_LINK_STATUS, &success);
  if (!success) {
    char info_log[512] = {};
    glGetProgramInfoLog(handle_, sizeof(info_log), NULL, info_log);
    wheels::Log() << "Error: cannot link program: " << info_log;

    throw std::runtime_error("cannot link program");
  }

  for (const auto& shader_handle : shaders_) {
    glDetachShader(handle_, shader_handle);
  }

  wheels::Log() << "program " << handle_ << "successfully linked";
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
}  // namespace GL
/*============================================================================*/
