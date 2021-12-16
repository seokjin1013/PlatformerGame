#pragma once

#define NOMINMAX
#include "Vec2.hpp"

namespace utility {
inline int get_index(const Vec2<int>& size, int idx, int i, int j);
inline int get_index(const Vec2<int>& size, int i, int j);
inline int get_index(const Vec2<int>& size, const Vec2<int> pos);
template <typename T>
inline T median(const T& x1, const T& x2, const T& x3);
template <typename T>
inline T lerp(const T& x1, const T& x2, double val);
}  // namespace utility

#include "Utility.inl"