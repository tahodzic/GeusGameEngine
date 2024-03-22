#pragma once

#include <iostream>
#include <stdexcept>

template<typename T>
class Vector3 {
public:
    T mX, mY, mZ;

    // Constructors
    Vector3() : mX(0), mY(0), mZ(0) {}
    Vector3(T x, T y, T z) : mX(x), mY(y), mZ(z) {}

    // Vector addition
    Vector3 operator+(const Vector3& v) const;

    // Vector subtraction
    Vector3 operator-(const Vector3& v) const;

    // Scalar multiplication
    Vector3 operator*(T scalar) const;

    // Dot product
    T dot(const Vector3<T>& v) const;

    // Cross product
    Vector3<T> cross(const Vector3<T>& v) const;

    // Magnitude
    T magnitude() const;

    // Normalization
    Vector3 normalize() const;

    // Output
    void print() const;

    const T& operator [] (uint8_t i) const;

    T& operator [] (uint8_t i);

};


template<typename T>
Vector3<T> Vector3<T>::operator+(const Vector3& v) const {
    return Vector3(mX + v.mX, mY + v.mY, mZ + v.mZ);
}

template<typename T>
Vector3<T> Vector3<T>::operator-(const Vector3& v) const {
    return Vector3(mX - v.mX, mY - v.mY, mZ - v.mZ);
}

template<typename T>
Vector3<T> Vector3<T>::operator*(T scalar) const {
    return Vector3(mX * scalar, mY * scalar, mZ * scalar);
}

template<typename T>
T Vector3<T>::dot(const Vector3<T>& v) const {
    return mX * v.mX + mY * v.mY + mZ * v.mZ;
}

template<typename T>
Vector3<T> Vector3<T>::cross(const Vector3<T>& v) const {
    return Vector3(
        mY * v.mZ - mZ * v.mY,
        mZ * v.mX - mX * v.mZ,
        mX * v.mY - mY * v.mX
    );
}

template<typename T>
void Vector3<T>::print() const
{
    std::cout << "(" << mX << ", " << mY << ", " << mZ << ")" << std::endl;
}

template<typename T>
T Vector3<T>::magnitude() const {
    return std::sqrt(mX * mX + mY * mY + mZ * mZ);
}

template<typename T>
Vector3<T> Vector3<T>::normalize() const {
    T mag = magnitude();
    if (mag == 0) return Vector3(0, 0, 0); // prevent division by zero
    return Vector3(mX / mag, mY / mag, mZ / mag);
}

template<typename T>
const T& Vector3<T>::operator [] (uint8_t i) const {
    // Note: Possible to also just return (&mX)[i], but this assumes that mX, mY, mZ are all ligned in memory, which is not guaranteed.
    switch (i) { case 0: return mX; case 1: return mY; case 2: return mZ; 
        default: throw std::runtime_error("Vector3: Index access failed.");
        }
}

template<typename T>
T& Vector3<T>::operator [] (uint8_t i) {
    // Note: Possible to also just return (&mX)[i], but this assumes that mX, mY, mZ are all ligned in memory, which is not guaranteed.
    switch (i) { case 0: return mX; case 1: return mY; case 2: return mZ;
        default: throw std::runtime_error("Vector3: Index access failed.");
    }
}