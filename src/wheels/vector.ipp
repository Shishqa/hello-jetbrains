/*============================================================================*/

#include <utility>

/*============================================================================*/
namespace wheels {
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

template <typename T>
Vector2<T>::Vector2(T x, T y) : x(std::move(x)), y(std::move(y)) {
}

template <typename T>
Vector2<T>& Vector2<T>::operator+=(const Vector2<T>& other) {
  x += other.x;
  y += other.y;
  return *this;
}

template <typename T>
Vector2<T> Vector2<T>::operator+(const Vector2<T>& other) const {
  return Vector2<T>(*this) += other;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
}
/*============================================================================*/
