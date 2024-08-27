#pragma once
#include "World.h"
#include "IRenderer.h"
#include "TextRenderer.h"
#include "Constants.h"
#include "WorldConstants.h"
#include "MediaLayer.h"

#include <functional>
#include <math.h>

World::World(std::shared_ptr<IMediaLayer> mediaLayer, CoordinateSystemGrid coordinateSystemGrid, ViewPort viewPort, UiManager uiManager)
	: mMediaLayer(mediaLayer),
	mCoordinateSystemGrid(coordinateSystemGrid),
	mCamera(),
	mInputManager(),
	mUiManager(uiManager),
	mObjectCount(0),
	mViewPort(viewPort)
{
	mInputManager.RegisterHandler(InputManager::EventType::KeyPress, std::bind(&World::HandleKeyDown, this, std::placeholders::_1));
	mInputManager.RegisterHandler(InputManager::EventType::MousePress, std::bind(&World::HandleMouseButtonDown, this, std::placeholders::_1));
	mInputManager.RegisterHandler(InputManager::EventType::MouseMove, std::bind(&World::HandleMouseMotion, this, std::placeholders::_1));
	mInputManager.RegisterHandler(InputManager::EventType::MouseWheel, std::bind(&World::HandleMouseWheel, this, std::placeholders::_1));
}

World::~World()
{
}

World World::CreateAndInitialize()
{
	using namespace WorldConstants;

	auto ml = MediaLayer::CreateAndSetup(windowTitle, windowPosX, windowPosY, windowWidth, windowHeight, canvasWidth, canvasHeight);
	
	auto uiManager = UiManager::CreateWithButtons(ml);
	/*

	Button mButtonReset(Vector2<int>(70, 25), Vector2<int>(10, 20), "Reset", ml);

	Button mButtonCreate(Vector2<int>(70, 25), Vector2<int>(10, 60), "Create", ml);*/

	auto csg = CoordinateSystemGrid::CreateWithGrid(ml);

	ViewPort vwp(ml, 100.0f, 100.0f, 640.0f, 480.0f);

	TextRenderer::Initialize(ml);

	World world(ml, csg, vwp, uiManager);

	return world;
}

void World::Render()
{
	mMediaLayer->PrepareRenderer();
	
	WorldMain();
	
	mMediaLayer->Render();
}

void World::AddObject(const Cube object)
{
	if (mObjectCount < WorldConstants::maxObjectsInWorld)
	{
		mObjects.push_back(object);
		mObjectCount++;
	}
}

Cube World::CreateCube(const float s, const float x, const float y, const float z)
{
	return Cube(mMediaLayer, s, x, y, z);
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
	mCamera.CalculateCameraRotation();

	mInputManager.HandleInput();

	mCamera.UpdateWorldToCameraMatrix();
}

void World::HandleKeyDown(const InputManager::InputEvent& inputEvent)
{
	switch (inputEvent.keyCode)
	{
	case InputManager::KeyCode::KeyR:
		ResetScene();
		break;
	}
}

void World::HandleMouseButtonDown(const InputManager::InputEvent& inputEvent)
{
	switch (inputEvent.keyCode)
	{
	case InputManager::KeyCode::MouseLeft:
		if (mButtonReset.IsClicked(inputEvent.mouseX, inputEvent.mouseY))
		{
			ResetScene();
		}

		if (mButtonCreate.IsClicked(inputEvent.mouseX, inputEvent.mouseY))
		{
			auto c = CreateCube(0.5f, 2.0f, 0.0f, 0.0f);
			AddObject(c);
		}
		break;
	default:
		break;
	}
}

void World::HandleMouseMotion(const InputManager::InputEvent & inputEvent)
{
	if (mInputManager.mInputState.leftMouseButtonDown)
	{
		int diffX, diffY;
		diffX = mInputManager.mInputState.prevMouseX - inputEvent.mouseX;
		diffY = mInputManager.mInputState.prevMouseY - inputEvent.mouseY;

		mInputManager.mInputState.prevMouseX = inputEvent.mouseX;
		mInputManager.mInputState.prevMouseY = inputEvent.mouseY;

		Vector3<float> translation((static_cast<float>(diffX)) / 50.0f, (static_cast<float>(-diffY)) / 50.0f, 0.0f);

		mCamera.MoveCamera(translation);
	}
	if (mInputManager.mInputState.rightMouseButtonDown)
	{
		int diffX, diffY;
		diffX = mInputManager.mInputState.prevMouseX - inputEvent.mouseX;
		diffY = mInputManager.mInputState.prevMouseY - inputEvent.mouseY;

		mInputManager.mInputState.prevMouseX = inputEvent.mouseX;
		mInputManager.mInputState.prevMouseY = inputEvent.mouseY;

		mCamera.YawCamera(static_cast<float>(diffX) * 0.01f);
		mCamera.PitchCamera(static_cast<float>(diffY) * 0.01f);
	}
}

void World::HandleMouseWheel(const InputManager::InputEvent& inputEvent)
{
	Vector3<float> translation(0.0f, 0.0f, static_cast<float>(-inputEvent.mouseWheelY));
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

void World::RenderButton()
{
	mButtonReset.Render(mWtcMatrix);

	mButtonCreate.Render(mWtcMatrix);
}

void World::RenderObjects()
{
	for (int i = 0; i < mObjectCount; i++)
	{
		mObjects[i].Render(mCamera.mWtcMatrix);
	}
}

void World::RenderCoordinateSystem()
{
	mCoordinateSystemGrid.Render(mCamera.mWtcMatrix);
}

void World::RenderViewPort()
{
	mViewPort.Render(mCamera.mWtcMatrix);
}

void World::WorldMain()
{
	RenderCoordinateSystem();
	RenderObjects();
	RenderButton();
	RenderViewPort();

	const bool inWorld = true;

	TextRenderer::print("X: " + std::to_string(mCamera.mPosition.mX), 100, 420, inWorld);
	TextRenderer::print("Y: " + std::to_string(mCamera.mPosition.mY), 100, 440, inWorld);
	TextRenderer::print("Z: " + std::to_string(mCamera.mPosition.mZ), 100, 460, inWorld);
}