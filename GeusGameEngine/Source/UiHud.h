#pragma once

#include "Vector2.h"
#include "World.h"
#include "Button.h"
#include "IMediaLayer.h"
#include "InputTypes.h"

#include <functional>

class UiHud
{
private:
	UiHud(std::string name, std::shared_ptr<IMediaLayer> mediaLayer);

public:
	~UiHud();

	std::string mName;

	std::shared_ptr<IMediaLayer> mMediaLayer;

	std::vector<Button> mButtons;

	static UiHud CreateHud(std::string name, std::shared_ptr<IMediaLayer> mediaLayer);

	void Render();

	void HandleEvent(const InputTypes::InputEvent& event);
	
	UiHud& WithButton(std::string name, Vector2<int> dimensions, Vector2<int> position, std::function<void()> callback);
};