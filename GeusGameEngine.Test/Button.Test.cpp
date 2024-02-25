#include "Button.h"
#include "Vector2Custom.h"


#include "pch.h" 

namespace ButtonTests
{
	class ButtonTest : public testing::Test
	{
	protected:
		ButtonTest() : mDimensions(1.0f, 2.0f), mPosition(3.0f, 4.0f), mLabel("Button1"), mButton(mDimensions, mPosition, mLabel)
		{}

		Vector2Custom<int> mDimensions;

		Vector2Custom<int> mPosition;

		std::string mLabel;

		Button mButton;
	};

	TEST_F(ButtonTest, IsInitializationCorrect)
	{
		std::string expectedLabel("Button1");

		Vector2Custom<int> expectedDimensions(1.0f, 2.0f);

		Vector2Custom<int> expectedPosition(3.0f, 4.0f);

		EXPECT_EQ(mDimensions.mX, expectedDimensions.mX);

		EXPECT_EQ(mDimensions.mY, expectedDimensions.mY);

		EXPECT_EQ(mPosition.mX, expectedPosition.mX);

		EXPECT_EQ(mPosition.mY, expectedPosition.mY);
		
		EXPECT_TRUE(mButton.mLabel == expectedLabel);
	}
}