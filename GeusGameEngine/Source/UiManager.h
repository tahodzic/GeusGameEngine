#pragma once

#include <vector>

#include "Button.h"
#include "IMediaLayer.h"

class UiManager
{
public:
	UiManager(std::vector<Button> buttons);

	~UiManager();

	std::vector<Button> mButtons;

	void RegisterButton(Button button);
	
	static UiManager CreateWithButtons(std::shared_ptr<IMediaLayer> mediaLayer);

private:

};

