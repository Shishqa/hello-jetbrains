/*============================================================================*/
#ifndef _GL_SHADER_HPP
#define _GL_SHADER_HPP
/*============================================================================*/

#include <cstdint>
#include <string_view>

/*============================================================================*/
namespace GL {
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

class Shader {
 public:
  explicit Shader(uint32_t type, std::string_view path);

  ~Shader();

  Shader(const Shader& other) = delete;
  Shader& operator=(const Shader& other) = delete;

  uint32_t Handle() const {
    return handle_;
  }

 private:
  void Compile(std::string_view source);

  uint32_t handle_;
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
}  // namespace GL
/*============================================================================*/
#endif /* ifndef _SHADER_HPP */
/*============================================================================*/
