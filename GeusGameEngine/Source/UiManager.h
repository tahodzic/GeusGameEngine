#pragma once

#include <vector>

#include "Button.h"

class UiManager
{
public:
	std::vector<Button> mButtons;

	void registerButton(Button button);
};

