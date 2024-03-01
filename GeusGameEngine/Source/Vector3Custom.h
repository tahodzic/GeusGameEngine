#pragma once

#include <iostream>
#include <stdexcept>

template<typename T>
class Vector3Custom {
public:
    T mX, mY, mZ;

    // Constructors
    Vector3Custom() : mX(0), mY(0), mZ(0) {}
    Vector3Custom(T x, T y, T z) : mX(x), mY(y), mZ(z) {}

    // Vector addition
    Vector3Custom operator+(const Vector3Custom& v) const;

    // Vector subtraction
    Vector3Custom operator-(const Vector3Custom& v) const;

    // Scalar multiplication
    Vector3Custom operator*(T scalar) const;

    // Dot product
    T dot(const Vector3Custom<T>& v) const;

    // Cross product
    Vector3Custom<T> cross(const Vector3Custom<T>& v) const;

    // Magnitude
    T magnitude() const;

    // Normalization
    Vector3Custom normalize() const;

    // Output
    void print() const;

    const T& operator [] (uint8_t i) const;

    T& operator [] (uint8_t i);

};

#include "Vector3Custom.h"


template<typename T>
Vector3Custom<T> Vector3Custom<T>::operator+(const Vector3Custom& v) const {
    return Vector3Custom(mX + v.mX, mY + v.mY, mZ + v.mZ);
}

template<typename T>
Vector3Custom<T> Vector3Custom<T>::operator-(const Vector3Custom& v) const {
    return Vector3Custom(mX - v.mX, mY - v.mY, mZ - v.mZ);
}

template<typename T>
Vector3Custom<T> Vector3Custom<T>::operator*(T scalar) const {
    return Vector3Custom(mX * scalar, mY * scalar, mZ * scalar);
}

template<typename T>
T Vector3Custom<T>::dot(const Vector3Custom<T>& v) const {
    return mX * v.mX + mY * v.mY + mZ * v.mZ;
}

template<typename T>
Vector3Custom<T> Vector3Custom<T>::cross(const Vector3Custom<T>& v) const {
    return Vector3Custom(
        mY * v.mZ - mZ * v.mY,
        mZ * v.mX - mX * v.mZ,
        mX * v.mY - mY * v.mX
    );
}

template<typename T>
void Vector3Custom<T>::print() const
{
    std::cout << "(" << mX << ", " << mY << ", " << mZ << ")" << std::endl;
}

template<typename T>
T Vector3Custom<T>::magnitude() const {
    return std::sqrt(mX * mX + mY * mY + mZ * mZ);
}

template<typename T>
Vector3Custom<T> Vector3Custom<T>::normalize() const {
    T mag = magnitude();
    if (mag == 0) return Vector3Custom(0, 0, 0); // prevent division by zero
    return Vector3Custom(mX / mag, mY / mag, mZ / mag);
}

template<typename T>
const T& Vector3Custom<T>::operator [] (uint8_t i) const {
    // Note: Possible to also just return (&mX)[i], but this assumes that mX, mY, mZ are all ligned in memory, which is not guaranteed.
    switch (i) { case 0: return mX; case 1: return mY; case 2: return mZ; 
        default: throw std::runtime_error("Vector3Custom: Index access failed.");
        }
}

template<typename T>
T& Vector3Custom<T>::operator [] (uint8_t i) {
    // Note: Possible to also just return (&mX)[i], but this assumes that mX, mY, mZ are all ligned in memory, which is not guaranteed.
    switch (i) { case 0: return mX; case 1: return mY; case 2: return mZ;
        default: throw std::runtime_error("Vector3Custom: Index access failed.");
    }
}