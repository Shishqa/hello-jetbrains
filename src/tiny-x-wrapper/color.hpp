#ifndef COLOR
#define COLOR

#include <stdint.h>
#include <cstdint>

struct Color {
  Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    data_[0] = static_cast<float>(r) / 255.;
    data_[1] = static_cast<float>(g) / 255.;
    data_[2] = static_cast<float>(b) / 255.;
    data_[3] = static_cast<float>(a) / 255.;
  }

  float data_[4];
};

#define UNPACK_COLOR( color ) \
  color.data_[0], color.data_[1], color.data_[2], color.data_[3]

#endif /* ifndef COLOR */
