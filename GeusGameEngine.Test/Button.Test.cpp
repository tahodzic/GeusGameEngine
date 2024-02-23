#include "Button.h"
#include "Vector2Custom.h"


#include "pch.h" 

namespace ButtonTests
{
	TEST(Label, IsCorrect)
	{
		Vector2Custom<int> dimensions(1.0f, 2.0f);
		Vector2Custom<int> position(3.0f, 4.0f);

		std::string label("Button1");
		std::string expected("Button1");

		Button button(dimensions, position, label);

		EXPECT_TRUE(label == expected);
	}

}