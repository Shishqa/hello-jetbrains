/*============================================================================*/
#ifndef WHEELS_VECTOR
#define WHEELS_VECTOR
/*============================================================================*/

#include <cstdint>

/*============================================================================*/
namespace wheels {
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/  

template <typename T>
struct Vector2 {
  Vector2() = default;

  Vector2(T x, T y);

  // Default copyable
  Vector2(const Vector2<T>& other) = default;
  Vector2<T>& operator=(const Vector2<T>& other) = default;

  // Default movable
  Vector2(Vector2<T>&& other) = default;
  Vector2<T>& operator=(Vector2<T>&& other) = default;

  // Arithmetics
  Vector2<T>& operator+=(const Vector2<T>& other);
  Vector2<T>  operator+ (const Vector2<T>& other) const;

  Vector2<T>& operator-=(const Vector2<T>& other);
  Vector2<T>  operator- (const Vector2<T>& other) const;

  Vector2<T>& operator*=(const T& coeff);
  Vector2<T>  operator* (const T& coeff) const;

  Vector2<T>& operator/=(const T& coeff);
  Vector2<T>  operator/ (const T& coeff) const;

  T x, y;
};

using Size2 = Vector2<uint32_t>;
using Pos2  = Vector2<int32_t>;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
}  // namespace wheels
/*============================================================================*/

#include "vector.ipp"

/*============================================================================*/
#endif /* ifndef WHEELS_VECTOR */
/*============================================================================*/
