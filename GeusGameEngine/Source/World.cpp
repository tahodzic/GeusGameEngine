#pragma once
#include "World.h"
#include "IRenderer.h"
#include "TextRenderer.h"
#include "Constants.h"
#include "WorldConstants.h"
#include "MediaLayer.h"

#include <functional>
#include <math.h>
//
//World::World(std::shared_ptr<IMediaLayer> mediaLayer, CoordinateSystemGrid coordinateSystemGrid, ViewPort viewPort, UiManager uiManager)
//	: mMediaLayer(mediaLayer),
//	mCoordinateSystemGrid(coordinateSystemGrid),
//	mCamera(),
//	mInputManager(),
//	mUiManager(uiManager),
//	mObjectCount(0),
//	mViewPort(viewPort)
//{
//	mInputManager.RegisterHandler(InputManager::EventType::KeyPress, std::bind(&World::HandleKeyDown, this, std::placeholders::_1));
//	mInputManager.RegisterHandler(InputManager::EventType::MousePress, std::bind(&World::HandleMouseButtonDown, this, std::placeholders::_1));
//	mInputManager.RegisterHandler(InputManager::EventType::MouseMove, std::bind(&World::HandleMouseMotion, this, std::placeholders::_1));
//	mInputManager.RegisterHandler(InputManager::EventType::MouseWheel, std::bind(&World::HandleMouseWheel, this, std::placeholders::_1));
//}

World::World(std::shared_ptr<IMediaLayer> mediaLayer, CoordinateSystemGrid coordinateSystemGrid, ViewPort viewPort)
	: mMediaLayer(mediaLayer),
	mCoordinateSystemGrid(coordinateSystemGrid),
	mCamera(),
	//mInputManager(),
	mObjectCount(0),
	mViewPort(viewPort),
	mInputState()
{
	//mInputManager.RegisterHandler(InputManager::EventType::KeyPress, std::bind(&World::HandleKeyDown, this, std::placeholders::_1));
	//mInputManager.RegisterHandler(InputManager::EventType::MousePress, std::bind(&World::HandleMouseButtonDown, this, std::placeholders::_1));
	//mInputManager.RegisterHandler(InputManager::EventType::MouseMove, std::bind(&World::HandleMouseMotion, this, std::placeholders::_1));
	//mInputManager.RegisterHandler(InputManager::EventType::MouseWheel, std::bind(&World::HandleMouseWheel, this, std::placeholders::_1));
}

World::~World()
{
}

//World World::CreateAndInitialize()
//{
//	using namespace WorldConstants;
//
//	auto ml = MediaLayer::CreateAndSetup(windowTitle, windowPosX, windowPosY, windowWidth, windowHeight, canvasWidth, canvasHeight);
//	
//	auto uiManager = UiManager::CreateWithButtons(ml);
//
//	auto csg = CoordinateSystemGrid::CreateWithGrid(ml);
//
//	ViewPort vwp(ml, 100.0f, 100.0f, 640.0f, 480.0f);
//
//	TextRenderer::Initialize(ml);
//
//	World world(ml, csg, vwp, uiManager);
//
//	return world;
//}

std::shared_ptr<World> World::CreateAndInitialize2(std::shared_ptr<IMediaLayer> mediaLayer)
{
	//using namespace WorldConstants;

	//auto ml = MediaLayer::CreateAndSetup(windowTitle, windowPosX, windowPosY, windowWidth, windowHeight, canvasWidth, canvasHeight);
	
	//auto uiManager = UiManager::CreateWithButtons(ml);

	auto csg = CoordinateSystemGrid::CreateWithGrid(mediaLayer);

	ViewPort vwp(mediaLayer, 100.0f, 100.0f, 640.0f, 480.0f);

	TextRenderer::Initialize(mediaLayer);

	return std::make_shared<World>(mediaLayer, csg, vwp);
}

void World::Render()
{
	//mMediaLayer->PrepareRenderer();
	
	WorldMain();
	
	//mMediaLayer->Render();
}

void World::AddObject(const Cube object)
{
	if (mObjectCount < WorldConstants::maxObjectsInWorld)
	{
		mObjects.push_back(object);
		mObjectCount++;
	}
}

void World::CreateCube(const float s, const float x, const float y, const float z)
{
	AddObject({mMediaLayer, s, x, y, z });
}

/*
Perspective Projection:

	Equations:
	x' = (x*f)/z
	y' = (y*f)/z
	z' = z
	where f = focal point of camera
*/

void World::HandleAction()
{
	//mCamera.CalculateCameraRotation();

	//mInputManager.HandleInput();

	//mCamera.UpdateWorldToCameraMatrix();
}


void World::HandleKeyDown(const InputTypes::InputEvent& event)
{
	switch (event.keyCode)
	{
	case InputTypes::KeyCode::KeyR:
		ResetScene();
		break;
	}
}

void World::HandleMouseButtonDown(const InputTypes::InputEvent& event)
{
	switch (event.keyCode)
	{
	case InputTypes::KeyCode::MouseLeft:
		//if (mButtonReset.IsClicked(inputEvent.mouseX, inputEvent.mouseY))
		//{
		//	ResetScene();
		//}

		//if (mButtonCreate.IsClicked(inputEvent.mouseX, inputEvent.mouseY))
		//{
		//	auto c = CreateCube(0.5f, 2.0f, 0.0f, 0.0f);
		//	AddObject(c);
		//}
		break;
	default:
		break;
	}
}

void World::HandleMouseMotion(const InputTypes::InputEvent& event)
{
	if (mInputState.leftMouseButtonDown)
	{
		int diffX, diffY;
		diffX = mInputState.prevMouseX - event.mouseX;
		diffY = mInputState.prevMouseY - event.mouseY;

		mInputState.prevMouseX = event.mouseX;
		mInputState.prevMouseY = event.mouseY;

		Vector3<float> translation((static_cast<float>(diffX)) / 50.0f, (static_cast<float>(-diffY)) / 50.0f, 0.0f);

		mCamera.MoveCamera(translation);
	}
	if (mInputState.rightMouseButtonDown)
	{
		int diffX, diffY;
		diffX = mInputState.prevMouseX - event.mouseX;
		diffY = mInputState.prevMouseY - event.mouseY;

		mInputState.prevMouseX = event.mouseX;
		mInputState.prevMouseY = event.mouseY;

		mCamera.YawCamera(static_cast<float>(diffX) * 0.01f);
		mCamera.PitchCamera(static_cast<float>(diffY) * 0.01f);
	}
}

void World::HandleMouseWheel(const InputTypes::InputEvent& event)
{
	Vector3<float> translation(0.0f, 0.0f, static_cast<float>(-event.mouseWheelY));
	mCamera.MoveCamera(translation);
}

void World::ResetScene()
{
	mCamera.Reset();
}

void World::CalculateWorldToCameraMatrix()
{
	mCamera.UpdateWorldToCameraMatrix();
}

//https://stackoverflow.com/a/45630217
//template <typename Args ...>
//void Logger::logging(Args ... args)
//{
//	std::stringstream ss;
//	(ss << ... << args);
//
//	Log4cpp::Category& myLogger = log4cpp::Category::getRoot();
//
//	myLogger.log(log4cpp::Priority::INFO, ss.str());
//}

//void World::RenderButton()
//{
	//for (auto& button : mUiManager.mButtons)
	//{
		//button.Render(mCamera.mWtcMatrix);
	//}
	//mButtonReset.Render(mWtcMatrix);

	//mButtonCreate.Render(mWtcMatrix);
//}

void World::RenderObjects()
{
	for (auto& obj : mObjects)
	{
		obj.Render(mCamera.mWtcMatrix);
	}
}

// TODO: Questionable if part of the world
void World::RenderCoordinateSystem()
{
	mCoordinateSystemGrid.Render(mCamera.mWtcMatrix);
}

// TODO: Probably not part of the world
void World::RenderViewPort()
{
	mViewPort.Render(Matrix44<float>{});
}

void World::WorldMain()
{

	mCamera.CalculateCameraRotation();

	//mInputManager.HandleInput();

	mCamera.UpdateWorldToCameraMatrix();

	RenderCoordinateSystem();
	RenderObjects();
	//RenderButton();
	RenderViewPort();

	const bool inWorld = true;

	TextRenderer::print("X: " + std::to_string(mCamera.mPosition.mX), 100, 420, inWorld);
	TextRenderer::print("Y: " + std::to_string(mCamera.mPosition.mY), 100, 440, inWorld);
	TextRenderer::print("Z: " + std::to_string(mCamera.mPosition.mZ), 100, 460, inWorld);
}

void World::Update(const InputTypes::InputEvent& event, [[maybe_unused]] const InputTypes::InputState& state)
{
	mInputState = state;

	switch (event.type)
	{
	case InputTypes::EventType::MouseWheel:
	{
		HandleMouseWheel(event);
		break;
	}
	case InputTypes::EventType::MouseMove:
	{
		HandleMouseMotion(event);
		break;
	}
	case InputTypes::EventType::MousePress:
	{
		HandleMouseButtonDown(event);
		break;
	}
	case InputTypes::EventType::KeyPress:
	{
		HandleKeyDown(event);
		break;
	}

	}
}
