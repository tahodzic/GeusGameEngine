#pragma once

#include <vector>
#include <memory>


#include "Button.h"
#include "IInputObserver.h"
#include "IInputObservable.h"
#include "IMediaLayer.h"
#include "World.h"
#include "UiHud.h"


class UiManager : public IInputObserver
{
private:
	std::vector<UiHud> mUiHuds;

public:
	//UiManager(std::vector<Button> buttons);

	UiManager(const std::vector<UiHud>& huds);

	~UiManager();

	void Render();

	//std::vector<Button> mButtons;

	//void RegisterButton(Button button);

	//static UiManager CreateWithButtons(std::shared_ptr<IMediaLayer> mediaLayer);

	void Update(const InputTypes::InputEvent& event, [[maybe_unused]] const InputTypes::InputState& state) override;

	static UiManager CreateWithHuds(std::shared_ptr<IMediaLayer> mediaLayer, std::shared_ptr<World> world);
};