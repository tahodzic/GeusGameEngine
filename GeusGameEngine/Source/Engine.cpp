#include "Engine.h"

#include "MediaLayer.h"
#include "WorldConstants.h"
#include "World.h"

Engine::Engine(std::shared_ptr<IMediaLayer> mediaLayer, UiManager uiManager, std::shared_ptr<World> world)
	: mMediaLayer(mediaLayer), mUiManager(uiManager), mWorld(world), mInputManager()
{}


void Engine::KickOff()
{
	mInputManager.AddObserver(mUiManager);
	mInputManager.AddObserver(*mWorld.get());

	for (;;)
	{
		mInputManager.HandleInput();
		mMediaLayer->PrepareRenderer();
		mUiManager.Render();
		//mWorld->HandleAction();
		mWorld->Render();
		mMediaLayer->Render();
	}
}

std::shared_ptr<Engine> Engine::CreateAndInitialize()
{
	using namespace WorldConstants;

	auto ml = MediaLayer::CreateAndSetup(windowTitle, windowPosX, windowPosY, windowWidth, windowHeight, canvasWidth, canvasHeight);

	auto world = World::CreateAndInitialize2(ml);

	//auto uiManager = UiManager::CreateWithButtons(ml);
	auto uiManager = UiManager::CreateWithHuds(ml, world);

	//auto csg = CoordinateSystemGrid::CreateWithGrid(ml);

	//ViewPort vwp(ml, 100.0f, 100.0f, 640.0f, 480.0f);

	//TextRenderer::Initialize(ml);

	//World world(ml, csg, vwp, uiManager);

	//return world;

	return std::make_shared<Engine>(ml, uiManager, world);
}