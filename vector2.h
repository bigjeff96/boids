#ifndef HEADER_VEC2
#define HEADER_VEC2

#include <algorithm>
#include <cmath>
#include <math.h>
#include <type_traits>

struct vec2 {

    float x;
    float y;

    // Methods
    vec2();
    vec2(float, float);
    float norm() const;
    vec2 &operator+=(const vec2 &);
    vec2 &operator-=(const vec2 &);
    friend void swap(vec2 &, vec2 &);
};

inline void swap(vec2 &first, vec2 &second) {
    using std::swap;
    swap(first.x, second.x);
    swap(first.y, second.y);
}

inline vec2 operator+(vec2 lhs, const vec2 &rhs) {
    lhs += rhs;
    return lhs;
}

inline vec2 operator-(vec2 lhs, const vec2 &rhs) {
    lhs -= rhs;
    return lhs;
}

inline float dot(const vec2 &lhs, const vec2 &rhs) { return lhs.x * rhs.x + lhs.y * rhs.y; }

inline float cross(const vec2 &lhs, const vec2 &rhs) { return lhs.x * rhs.y - lhs.y * rhs.x; }

inline vec2 cross(const float &VectorInZaxis, const vec2 &rhs) {
    return vec2(-VectorInZaxis * rhs.y, VectorInZaxis * rhs.x);
}

inline vec2 operator*(vec2 lhs, const float Coefficient) {
    lhs.x *= Coefficient;
    lhs.y *= Coefficient;
    return lhs;
}

inline vec2 operator*(const float Coefficient, vec2 rhs) {
    rhs.x *= Coefficient;
    rhs.y *= Coefficient;
    return rhs;
}
#endif
