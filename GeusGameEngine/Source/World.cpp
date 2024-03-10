#pragma once
#include "World.h"
#include "IRenderer.h"
#include "TextRenderer.h"
#include "Constants.h"
#include "WorldConstants.h"

#include <math.h>

World::World(CoordinateSystemGrid coordinateSystemGrid, Camera camera) :
	mCoordinateSystemGrid(coordinateSystemGrid),
	mCamera(camera),
	mButtonReset(Vector2Custom<int>(70,25), Vector2Custom<int>(10, 20), "Reset"),
	mButtonCreate(Vector2Custom<int>(70, 25), Vector2Custom<int>(10, 60), "Create"),
	mSdlEvent(),
	mMousePrevX(0), 
	mMousePrevY(0),
	mMouseDiffX(0), 
	mMouseDiffY(0),
	mObjectCount(0)
{
}

World::~World()
{
}

World World::CreateAndInitialize()
{
	using namespace WorldConstants;

	Camera camera;

	MediaLayer::getInstance().Initialize(windowTitle, windowPosX, windowPosY, windowWidth, windowHeight, canvasWidth, canvasHeight);
	
	CoordinateSystemGrid csg(20.0f, MediaLayer::getInstance().GetFontHandler(), MediaLayer::getInstance().GetRenderer());

	World world(csg, camera);

	return world;
}

void World::Render()
{
	MediaLayer::getInstance().PrepareRenderer();
	
	WorldMain();
	
	MediaLayer::getInstance().Render();
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
	auto ren = MediaLayer::getInstance().GetRenderer();
	return Cube(ren, s, x, y, z);
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

	while (PollKeyEvents())
	{
		HandleKeyEvents();
	}

	mCamera.UpdateWorldToCameraMatrix();
}

void World::HandleKeyEvents()
{
	static bool leftMouseButtonDown = false; // TODO: make own input class

	float change = 2.0f*static_cast<float>(Constants::pi)/8.0f;

	change *= 0.1f;

	switch (mSdlEvent.type)
	{
	case SDL_KEYDOWN:
	{
		switch (mSdlEvent.key.keysym.sym)
		{
		case SDLK_w:
			mCamera.PitchCamera(-change);
			break;

		case SDLK_s:
			mCamera.PitchCamera(change);
			break;

		case SDLK_a:
			mCamera.YawCamera(-change);
			break;

		case SDLK_d:
			mCamera.YawCamera(change);
			break;

		case SDLK_q:
			mCamera.RollCamera(-change);
			break;

		case SDLK_e:
			mCamera.RollCamera(change);
			break;

		case SDLK_r:
			ResetScene();
			break;
		}
		break;
	}
	case SDL_MOUSEBUTTONDOWN:
	{
		if (mSdlEvent.button.button == SDL_BUTTON_LEFT)
		{
			leftMouseButtonDown = true;
			mMousePrevX = mSdlEvent.button.x;
			mMousePrevY = mSdlEvent.button.y;
			if (mButtonReset.IsClicked(mSdlEvent.button.x, mSdlEvent.button.y))
			{
				ResetScene();
			}

			if (mButtonCreate.IsClicked(mSdlEvent.button.x, mSdlEvent.button.y))
			{
				auto c = CreateCube(0.5f, 2.0f, 0.0f, 0.0f);
				AddObject(c);
			}
		}
		break;
	}
	case SDL_MOUSEBUTTONUP:
	{
		if (mSdlEvent.button.button == SDL_BUTTON_LEFT)
		{
			leftMouseButtonDown = false;
		}
		break;
	}
	case SDL_MOUSEMOTION:
	{
		if (leftMouseButtonDown)
		{
			mMouseDiffX = mMousePrevX - mSdlEvent.button.x;
			mMouseDiffY = mMousePrevY - mSdlEvent.button.y;

			mMousePrevX = mSdlEvent.button.x;
			mMousePrevY = mSdlEvent.button.y;
			
			Vector3Custom<float> translation((static_cast<float>(mMouseDiffX)) / 50.0f, (static_cast<float>(-mMouseDiffY)) / 50.0f, 0.0f);
			mCamera.MoveCamera(translation);
		}
		break;
	}
	case SDL_MOUSEWHEEL:
	{
		Vector3Custom<float> translation(0.0f, 0.0f, static_cast<float>(-mSdlEvent.wheel.y));
		mCamera.MoveCamera(translation);
		break;
	}
	default:
		break;
	}
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
	bool inWorld = false;
	TextRenderer::print(mButtonReset.mLabel,
		mButtonReset.mDimensions.mX + mButtonReset.mPosition.mX,
		mButtonReset.mDimensions.mY + mButtonReset.mPosition.mY,
		inWorld);
	TextRenderer::print(mButtonCreate.mLabel,
		mButtonCreate.mDimensions.mX + mButtonCreate.mPosition.mX,
		mButtonCreate.mDimensions.mY + mButtonCreate.mPosition.mY,
		inWorld);
	UiDrawRectangle(mButtonReset.mDimensions, mButtonReset.mPosition, inWorld);
	UiDrawRectangle(mButtonCreate.mDimensions, mButtonCreate.mPosition, inWorld);
}

void World::UiDrawRectangle(Vector2Custom<int> dimensions, Vector2Custom<int> position, const bool inWorld)
{
	MediaLayer::getInstance().RenderRect(dimensions.mX, dimensions.mY, position.mX, position.mY, inWorld);
}

void World::RenderObjects()
{
	for (int i = 0; i < mObjectCount; i++)
	{
		mObjects[i].Render(mCamera.mWtcMatrix);
	}
}

void World::RenderCoordinateSystem() const
{
	mCoordinateSystemGrid.Render(mCamera.mWtcMatrix);
}

void World::WorldMain()
{
	RenderCoordinateSystem();
	RenderObjects();
	RenderButton();

	const bool inWorld = true;

	TextRenderer::print("X: " + std::to_string(mCamera.mPosition.mX), 100, 420, inWorld);
	TextRenderer::print("Y: " + std::to_string(mCamera.mPosition.mY), 100, 440, inWorld);
	TextRenderer::print("Z: " + std::to_string(mCamera.mPosition.mZ), 100, 460, inWorld);
}