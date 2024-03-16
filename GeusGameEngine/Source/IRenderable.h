#pragma once

#include "Matrix44.h"

class IRenderable
{
	virtual void Render(const Matrix44<float>& matrix)  = 0;
};

