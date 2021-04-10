#ifndef _SHADER_HPP
#define _SHADER_HPP

#include <stdint.h>
#include <cstdint>
#include <string_view>

namespace GL {

class Shader {
 public:
  explicit Shader(uint32_t type, std::string_view path); 

  uint32_t Handle() const {
    return handle_;
  }

  ~Shader();

 private:
  void Compile(std::string_view source);

  uint32_t handle_;
};


}


#endif /* ifndef _SHADER_HPP */
