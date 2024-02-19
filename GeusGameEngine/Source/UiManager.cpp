#pragma once

#include "UiManager.h"

void UiManager::registerButton(Button button)
{
	mButtons.push_back(button);
}
