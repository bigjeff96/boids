#include "vector2.h"
#include <algorithm>
#include <cmath>
#include <math.h>
#include <type_traits>

vec2::vec2()
{
  x = 0.;
  y = 0.;
}

vec2::vec2(float InitX, float InitY)
{
  x = InitX;
  y = InitY;
}

float
vec2::norm() const
{
  return std::sqrt(x * x + y * y);
}

vec2&
vec2::operator+=(const vec2& rhs)
{
  x += rhs.x;
  y += rhs.y;
  return *this;
}

vec2&
vec2::operator-=(const vec2& rhs)
{
  x -= rhs.x;
  y -= rhs.y;
  return *this;
}
