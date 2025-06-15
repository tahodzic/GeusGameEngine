#include "Engine.h"
#include "MediaLayer.h"
#include "World.h"
#include "WorldConstants.h"

Engine::Engine(std::shared_ptr<IMediaLayer> mediaLayer, UiManager uiManager, std::shared_ptr<World> world)
	: mMediaLayer(mediaLayer), mUiManager(uiManager), mWorld(world), mInputManager()
{}


void Engine::KickOff()
{
	mInputManager.AddObserver(mUiManager);

	// TODO: Find a better way to store observers
	mInputManager.AddObserver(*mWorld.get()); 

	for (;;)
	{
		mInputManager.HandleInput();
		mMediaLayer->PrepareRenderer();
		mUiManager.Render();
		mWorld->Render();
		mMediaLayer->Render();
	}
}

std::shared_ptr<Engine> Engine::CreateAndInitialize()
{
	using namespace WorldConstants;

	auto ml = MediaLayer::CreateAndSetup(windowTitle, windowPosX, windowPosY, windowWidth, windowHeight, canvasWidth, canvasHeight);

	auto world = World::CreateAndInitialize(ml);

	auto uiManager = UiManager::CreateWithHuds(ml, world);

	return std::make_shared<Engine>(ml, uiManager, world);
}