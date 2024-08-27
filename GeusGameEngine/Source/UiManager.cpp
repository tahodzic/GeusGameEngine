#pragma once

#include "UiManager.h"

UiManager::UiManager(std::vector<Button> buttons)
{
}

UiManager::~UiManager()
{
}

void UiManager::RegisterButton(Button button)
{
	mButtons.push_back(button);
}

UiManager UiManager::CreateWithButtons(std::shared_ptr<IMediaLayer> mediaLayer)
{
	Button resetButton(Vector2<int>(70, 25), Vector2<int>(10, 20), "Reset", mediaLayer);

	Button createButton(Vector2<int>(70, 25), Vector2<int>(10, 60), "Create", mediaLayer);
	
	return UiManager({ resetButton, createButton });
}
