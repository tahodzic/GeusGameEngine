#include "InputTypes.h"
#include "UiHud.h"

#include <algorithm>
#include <ranges>

UiHud::UiHud(std::string name, std::shared_ptr<IMediaLayer> mediaLayer) : mName(name), mMediaLayer(mediaLayer)
{
}

UiHud::~UiHud()
{
}

UiHud UiHud::CreateHud(std::string name, std::shared_ptr<IMediaLayer> mediaLayer)
{
	return UiHud(name, mediaLayer);
}

void UiHud::Render()
{
	for (auto& button : mButtons)
	{
		// TODO: Bad design where buttons also implement IRenderable that has a method that needs a Matrix
		button.Render(Matrix44<float>{});
	}
}

void UiHud::HandleEvent(const InputTypes::InputEvent& event)
{
	for (auto& button : mButtons)
	{
		if (button.IsClicked(event.mouseX, event.mouseY) && event.type == InputTypes::EventType::MousePress)
		{
			button.OnClick();
		}
	}
}

// TODO: Investigate why the EFF this doesnt work as expected
//void UiHud::HandleEvent(const InputTypes::InputEvent& event)
//{
//	std::ranges::for_each(std::next(mButtons.begin()), mButtons.end(), [x = event.mouseX, y = event.mouseY](Button& button) {
//		if (button.IsClicked(x, y))
//		{
//			button.OnClick();
//		}
//	});
//}

UiHud& UiHud::WithButton(std::string name, Vector2<int> dimensions, Vector2<int> position, std::function<void()> callback)
{
	mButtons.push_back(Button{ dimensions, position, name, callback, mMediaLayer });
	
	return *this;
}