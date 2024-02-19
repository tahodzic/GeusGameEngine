#pragma once
#include <iostream>
#include <cmath>
#include <limits>

template<typename T>
class Vector2Custom
{
public:
    Vector2Custom() : mX(0), mY(0) {}
    Vector2Custom(T xx) : mX(xx), mY(xx) {}
    Vector2Custom(T xx, T yy) : mX(xx), mY(yy) {}
    Vector2Custom operator + (const Vector2Custom& v) const
    {
        return Vector2Custom(mX + v.mX, mY + v.mY);
    }
    Vector2Custom operator / (const T& r) const
    {
        return Vector2Custom(mX / r, mY / r);
    }
    Vector2Custom operator * (const T& r) const
    {
        return Vector2Custom(mX * r, mY * r);
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

    Vector2Custom& operator /= (const T& r)
    {
        mX /= r, mY /= r; return *this;
    }
    Vector2Custom& operator *= (const T& r)
    {
        mX *= r, mY *= r; return *this;
    }

    friend std::ostream& operator << (std::ostream& s, const Vector2Custom<T>& v)
    {
        return s << '[' << v.mX << ' ' << v.mY << ']';
    }

    friend Vector2Custom operator * (const T& r, const Vector2Custom<T>& v)
    {
        return Vector2Custom(v.mX * r, v.mY * r);
    }
    T mX, mY;
};
