#include "UiManager.h"

#include <algorithm>
#include <functional>
#include <ranges>

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

UiManager UiManager::CreateWithHuds(std::shared_ptr<IMediaLayer> mediaLayer, std::shared_ptr<World> world)
{
	std::vector<UiHud> huds;

	huds.push_back(CreateNavigationHud(mediaLayer, world));

	return UiManager(huds);
}