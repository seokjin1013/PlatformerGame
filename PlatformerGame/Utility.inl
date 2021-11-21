inline int utility::get_index(const Vec2<int>& size, int idx, int i, int j) {
    return size.y * size.x * idx + size.x * i + j;
}

inline int utility::get_index(const Vec2<int>& size, int i, int j) {
    return size.x * i + j;
}

inline int utility::get_index(const Vec2<int>& size, Vec2<int> pos) {
    return size.x * pos.y + pos.x;
}

template <typename T>
inline T utility::median(const T& x1, const T& x2, const T& x3) {
    auto min_val = x1 < x2 ? x1 : x2;
    min_val = min_val < x3 ? min_val : x3;
    auto max_val = x1 > x2 ? x1 : x2;
    max_val = max_val > x3 ? max_val : x3;
    return x1 + x2 + x3 - min_val - max_val;
}

template <typename T>
inline T utility::lerp(const T& x1, const T& x2, double val) {
    return static_cast<T>(x1 + (x2 - x1) * val);
}