#pragma once

#include "Vector3Custom.h"

class Plane
{
public:
	Plane();

	Plane(float a, float b, float c, float d);
	
	~Plane();
	
	float mA, mB, mC, mD; // Plane equation coefficients

	void set(float a, float b, float c, float d);
	
	void normalize();

	float distanceToPoint(const Vector3Custom<float>& point) const;

	bool isPointInFront(const Vector3Custom<float>& point) const;

	float& operator [] (uint8_t i);
};


