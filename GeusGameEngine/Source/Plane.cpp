#include "Plane.h"

Plane::~Plane()
{
}

Plane::Plane() : mA(0), mB(0), mC(0), mD(0)
{
}

Plane::Plane(float a, float b, float c, float d) : mA(a), mB(b), mC(c), mD(d)
{
}

void Plane::set(float a, float b, float c, float d)
{
	mA = a;
	mB = b;
	mC = c;
	mD = d;
}

void Plane::normalize()
{
	float length = std::sqrt(mA * mA + mB * mB + mC * mC);
	mA /= length;
	mB /= length;
	mC /= length;
	mD /= length;
}

float Plane::distanceToPoint(const Vector3<float>& point) const
{
	return mA * point.mX + mB * point.mY + mC * point.mZ + mD;
}

bool Plane::isPointInFront(const Vector3<float>& point) const
{
	return distanceToPoint(point) > 0;
}

float& Plane::operator [] (uint8_t i)
{
	switch (i)
	{
	case 0: return mA; case 1: return mB; case 2: return mC; case 3: return mD;
	default: throw std::runtime_error("Plane: Index access failed.");
	}
}
