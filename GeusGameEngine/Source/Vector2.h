#pragma once
#include <iostream>
#include <cmath>
#include <limits>

template<typename T>
class Vector2
{
public:
    Vector2() : mX(0), mY(0) {}
    Vector2(T xx) : mX(xx), mY(xx) {}
    Vector2(T xx, T yy) : mX(xx), mY(yy) {}
    Vector2 operator + (const Vector2& v) const
    {
        return Vector2(mX + v.mX, mY + v.mY);
    }
    Vector2 operator / (const T& r) const
    {
        return Vector2(mX / r, mY / r);
    }
    Vector2 operator * (const T& r) const
    {
        return Vector2(mX * r, mY * r);
    }
    
    constexpr bool isOrigin() const
    {
        if constexpr (std::is_floating_point_v<T>)
        {
            const T epsilon = std::numeric_limits<T>::epsilon();
            return std::abs(mX) <= epsilon && std::abs(mY) <= epsilon;
        }
        else
        {
            return mX == T(0) && mY == T(0);
        }
    }

    Vector2& operator /= (const T& r)
    {
        mX /= r, mY /= r; return *this;
    }
    Vector2& operator *= (const T& r)
    {
        mX *= r, mY *= r; return *this;
    }

    friend std::ostream& operator << (std::ostream& s, const Vector2<T>& v)
    {
        return s << '[' << v.mX << ' ' << v.mY << ']';
    }

    friend Vector2 operator * (const T& r, const Vector2<T>& v)
    {
        return Vector2(v.mX * r, v.mY * r);
    }
    T mX, mY;
};
