#pragma once

#include <cmath>
#include <iostream>

template <typename Elem>
class Vec2;

template <typename Elem>
std::istream& operator>>(std::istream& is, Vec2<Elem>& self);
template <typename Elem>
std::ostream& operator<<(std::ostream& os, const Vec2<Elem>& self);

template <typename Elem = double>
class Vec2 {
public:
    Elem x = 0, y = 0;
    Vec2() = default;
    template <typename T>
    Vec2(const Vec2<T>& o);
    Vec2(Elem v);
    Vec2(Elem x, Elem y);
    Vec2<Elem> operator+(const Vec2<Elem>& rhs) const;
    Vec2<Elem> operator-(const Vec2<Elem>& rhs) const;
    Vec2<Elem> operator*(const Vec2<Elem>& rhs) const;
    Vec2<Elem> operator/(const Vec2<Elem>& rhs) const;
    Vec2<Elem>& operator+=(const Vec2<Elem>& rhs);
    Vec2<Elem>& operator-=(const Vec2<Elem>& rhs);
    Vec2<Elem>& operator*=(const Vec2<Elem>& rhs);
    Vec2<Elem>& operator/=(const Vec2<Elem>& rhs);
    bool operator==(const Vec2<Elem>& rhs) const;
    bool operator!=(const Vec2<Elem>& rhs) const;
    friend std::istream& operator>><Elem>(std::istream& is, Vec2<Elem>& self);
    friend std::ostream& operator<<<Elem>(std::ostream& os, const Vec2<Elem>& self);
    Elem dot(const Vec2<Elem>& rhs) const;
    Elem cross(const Vec2<Elem>& rhs) const;
    Elem norm() const;
    void normalize();
    Elem area() const;
    static Vec2<Elem> LEFT();
    static Vec2<Elem> RIGHT();
    static Vec2<Elem> UP();
    static Vec2<Elem> DOWN();
};

#include "Vec2.inl"