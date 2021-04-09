#ifndef _SHADER_HPP
#define _SHADER_HPP

#include <stdint.h>
#include <cstdint>

namespace GL {

class Shader {
 public:
  explicit Shader(uint32_t type, const char* source); 

  uint32_t Handle() const {
    return handle_;
  }

  ~Shader();

 private:
  uint32_t handle_;
};


}


#endif /* ifndef _SHADER_HPP */
