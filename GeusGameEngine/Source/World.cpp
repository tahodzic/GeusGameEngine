#pragma once
#include "World.h"
#include "IRenderer.h"
#include "TextRenderer.h"
#include "Constants.h"
#include "WorldConstants.h"
#include "MediaLayer.h"

#include <functional>
#include <math.h>

World::World(std::shared_ptr<IMediaLayer> mediaLayer, CoordinateSystemGrid coordinateSystemGrid, ViewPort viewPort, Button button1, Button button2)
	: mMediaLayer(mediaLayer),
	mCoordinateSystemGrid(coordinateSystemGrid),
	mCamera(),
	mInputManager(),
	mButtonReset(button1),
	mButtonCreate(button2),
	mSdlEvent(),
	mMousePrevX(0), 
	mMousePrevY(0),
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

	Button mButtonReset(Vector2<int>(70, 25), Vector2<int>(10, 20), "Reset", ml);

	Button mButtonCreate(Vector2<int>(70, 25), Vector2<int>(10, 60), "Create", ml);

	auto csg = CoordinateSystemGrid::CreateWithGrid(ml);

	ViewPort vwp(ml, 100.0f, 100.0f, 640.0f, 480.0f);

	TextRenderer::Initialize(ml);

	World world(ml, csg, vwp, mButtonReset, mButtonCreate);

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

bool World::PollKeyEvents()
{
	return SDL_PollEvent(&mSdlEvent) != 0;
}

void World::HandleAction()
{
	mCamera.CalculateCameraRotation();

	mInputManager.HandleInput();
	
	//while (PollKeyEvents())
	//{
	//	HandleKeyEvents();
	//}

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
	std::string output = "MouseMotion: leftMousButtonDown is: " + std::to_string(mInputManager.mInputState.leftMouseButtonDown) + "\n";
	OutputDebugStringA(output.c_str());
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

void World::HandleKeyEvents()
{
	//static bool leftMouseButtonDown = false; // TODO: make own input class
	//static bool rightMouseButtonDown = false; // TODO: make own input class

	//float change = 2.0f*static_cast<float>(Constants::pi)/8.0f;

	//change *= 0.1f;

	//switch (mSdlEvent.type)
	//{
	//case SDL_KEYDOWN:
	//{
	//	switch (mSdlEvent.key.keysym.sym)
	//	{
	//	case SDLK_r:
	//		ResetScene();
	//		break;
	//	}
	//	break;
	//}
	//case SDL_MOUSEBUTTONDOWN:
	//{
	//	if (mSdlEvent.button.button == SDL_BUTTON_LEFT)
	//	{
	//		leftMouseButtonDown = true;
	//		mMousePrevX = mSdlEvent.button.x;
	//		mMousePrevY = mSdlEvent.button.y;
	//		if (mButtonReset.IsClicked(mSdlEvent.button.x, mSdlEvent.button.y))
	//		{
	//			ResetScene();
	//		}

	//		if (mButtonCreate.IsClicked(mSdlEvent.button.x, mSdlEvent.button.y))
	//		{
	//			auto c = CreateCube(0.5f, 2.0f, 0.0f, 0.0f);
	//			AddObject(c);
	//		}
	//	}
	//	if (mSdlEvent.button.button == SDL_BUTTON_RIGHT)
	//	{
	//		rightMouseButtonDown = true;
	//		mMousePrevX = mSdlEvent.button.x;
	//		mMousePrevY = mSdlEvent.button.y;
	//	}
	//	break;
	//}
	//case SDL_MOUSEBUTTONUP:
	//{
	//	if (mSdlEvent.button.button == SDL_BUTTON_LEFT)
	//	{
	//		leftMouseButtonDown = false;
	//	}
	//	if (mSdlEvent.button.button == SDL_BUTTON_RIGHT)
	//	{
	//		rightMouseButtonDown = false;
	//	}
	//	break;
	//}
	//case SDL_MOUSEMOTION:
	//{
	//	if (leftMouseButtonDown)
	//	{
	//		mMouseDiffX = mMousePrevX - mSdlEvent.button.x;
	//		mMouseDiffY = mMousePrevY - mSdlEvent.button.y;

	//		mMousePrevX = mSdlEvent.button.x;
	//		mMousePrevY = mSdlEvent.button.y;
	//		
	//		Vector3<float> translation((static_cast<float>(mMouseDiffX)) / 50.0f, (static_cast<float>(-mMouseDiffY)) / 50.0f, 0.0f);

	//		mCamera.MoveCamera(translation);
	//	}
	//	if (rightMouseButtonDown)
	//	{
	//		mMouseDiffX = mMousePrevX - mSdlEvent.button.x;
	//		mMouseDiffY = mMousePrevY - mSdlEvent.button.y;

	//		mMousePrevX = mSdlEvent.button.x;
	//		mMousePrevY = mSdlEvent.button.y;

	//		mCamera.YawCamera(static_cast<float>(mMouseDiffX) * 0.01f);
	//		mCamera.PitchCamera(static_cast<float>(mMouseDiffY) * 0.01f);
	//	}
	//	break;
	//}
	//case SDL_MOUSEWHEEL:
	//{
	//	Vector3<float> translation(0.0f, 0.0f, static_cast<float>(-mSdlEvent.wheel.y));
	//	mCamera.MoveCamera(translation);
	//	break;
	//}
	//default:
	//	break;
	//}
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