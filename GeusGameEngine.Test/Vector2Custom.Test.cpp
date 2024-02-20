#include "Vector2Custom.h"

#include "pch.h" 

namespace Vector2CustomTests
{ 
TEST(Addition, TwoVectors)
{
	Vector2Custom<float> v1(1.0f, 2.0f);
	Vector2Custom<float> v2(3.0f, 4.0f);
	Vector2Custom<float> vExpected(4.0f, 6.0f);

	auto vResult = v1 + v2;
	
	EXPECT_FLOAT_EQ(vExpected.mX, vResult.mX);
	EXPECT_FLOAT_EQ(vExpected.mY, vResult.mY);
}

}