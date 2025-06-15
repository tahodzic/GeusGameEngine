#pragma once

#include "IMediaLayer.h"
#include "InputManager.h"
#include "UiManager.h"

#include <memory>

class Engine
{
public:
	Engine(std::shared_ptr<IMediaLayer> mediaLayer, UiManager uiManager, std::shared_ptr<World> world);

	std::shared_ptr<IMediaLayer> mMediaLayer;

	InputManager mInputManager;

	UiManager mUiManager;

	std::shared_ptr<World> mWorld;

	void KickOff();

	static std::shared_ptr<Engine> CreateAndInitialize();
};

