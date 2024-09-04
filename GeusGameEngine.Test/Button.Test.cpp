#include "Button.h"
#include "Vector2.h"
#include "IMediaLayer.h"
#include "MediaLayerMock.h"

#include "pch.h" 

namespace ButtonTests
{
	class ButtonTest : public testing::Test
	{
	protected:
		ButtonTest() : mDimensions(1, 2), mPosition(3, 4), mLabel("Button1"), mFunction([](){}),
			mButton(mDimensions, mPosition, mLabel, mFunction, std::make_shared<MediaLayerMock>())
		{}

		Vector2<int> mDimensions;

		std::function<void()> mFunction;
		
		Vector2<int> mPosition;

		std::string mLabel;

		Button mButton;
	};

	TEST_F(ButtonTest, IsInitializationCorrect)
	{
		std::string expectedLabel("Button1");

		Vector2<int> expectedDimensions(1, 2);

		Vector2<int> expectedPosition(3, 4);

		EXPECT_EQ(mDimensions.mX, expectedDimensions.mX);

		EXPECT_EQ(mDimensions.mY, expectedDimensions.mY);

		EXPECT_EQ(mPosition.mX, expectedPosition.mX);

		EXPECT_EQ(mPosition.mY, expectedPosition.mY);
		
		EXPECT_TRUE(mButton.mLabel == expectedLabel);
	}
}