#pragma once

#include "UiManager.h"

#include <functional>
#include <algorithm>
#include <ranges>

//UiManager::UiManager(std::vector<Button> buttons) : mButtons(buttons)
//{
//}

UiManager::UiManager(const std::vector<UiHud>& huds) : mUiHuds(huds)
{
}

UiManager::~UiManager()
{
}

void UiManager::Render()
{
	for (auto& hud : mUiHuds)
	{
		hud.Render();
	}
}

//void UiManager::RegisterButton(Button button)
//{
//	mButtons.push_back(button);
//}
//
//UiManager UiManager::CreateWithButtons(std::shared_ptr<IMediaLayer> mediaLayer)
//{
//	Button resetButton(Vector2<int>(70, 25), Vector2<int>(10, 20), "Reset", mediaLayer);
//
//	Button createButton(Vector2<int>(70, 25), Vector2<int>(10, 60), "Create", mediaLayer);
//	
//	return UiManager({ resetButton, createButton });
//}

static void Reset(std::shared_ptr<World> world)
{
	world->ResetScene();
}

static void Create(std::shared_ptr<World> world)
{
	world->CreateCube(0.5f, 2.0f, 0.0f, 0.0f);
}

static UiHud CreateNavigationHud(std::shared_ptr<IMediaLayer> mediaLayer, std::shared_ptr<World> world)
{
	auto naviHud = UiHud::CreateHud("HudName", mediaLayer)
		.WithButton("Reset", Vector2<int>(70, 25), Vector2<int>(10, 20), [world]() {Reset(world); })
		.WithButton("Create", Vector2<int>(70, 25), Vector2<int>(10, 60), [world]() {Create(world); });

	return naviHud;
}

void UiManager::Update(const InputTypes::InputEvent& event, [[maybe_unused]] const InputTypes::InputState& state)
{
	for (auto& hud : mUiHuds)
	{
		hud.HandleEvent(event);
	}
}

// TODO: Investigate why below ranges doesnt work as exptected
//void UiManager::Update(const InputTypes::InputEvent& event, [[maybe_unused]] const InputTypes::InputState& state)
//{
//	std::ranges::for_each(std::next(mUiHuds.begin()), mUiHuds.end(), [event](UiHud& uiHud) {
//		uiHud.HandleEvent(event);
//	});
//}

UiManager UiManager::CreateWithHuds(std::shared_ptr<IMediaLayer> mediaLayer, std::shared_ptr<World> world)
{
	std::vector<UiHud> huds;

	huds.push_back(CreateNavigationHud(mediaLayer, world));

	//Button resetButton(Vector2<int>(70, 25), Vector2<int>(10, 20), "Reset", mediaLayer);

	//Button createButton(Vector2<int>(70, 25), Vector2<int>(10, 60), "Create", mediaLayer);

	return UiManager(huds);
}