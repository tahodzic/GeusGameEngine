#pragma once
#include "World.h"
#include "IRenderer.h"
#include "TextRenderer.h"
#include "Constants.h"

#include <math.h>

World::World() : 
	mCoordinateSystemGrid(20.0f), 
	mButtonReset(Vector2Custom<int>(70,25), Vector2Custom<int>(10, 20), "Reset")
{
	mObjectCount = 0;
}

World::~World()
{
}

void World::init()
{
	MediaLayer::getInstance().Initialize(sTitle, sWindowPosX, sWindowPosY, sWindowWidth, sWindowHeight, sCanvasWidth, sCanvasHeight, mCamera.kProjectionMatrixRef);
}

void World::render()
{
	MediaLayer::getInstance().PrepareRenderer();
	
	worldMain();
	
	MediaLayer::getInstance().Render();
}

void World::addObject(Cube* object)
{
	if (mObjectCount < sMaxObjectsInWorld)
	{
		mObjects[mObjectCount] = object;
		mObjectCount++;
	}
}

/*
Perspective Projection:

	Equations:
	x' = (x*f)/z
	y' = (y*f)/z
	z' = z
	where f = focal point of camera
*/


bool World::pollKeyEvents()
{
	return SDL_PollEvent(&mpSdlEvent) != 0;
}

void World::handleAction()
{
	mCamera.calculateCameraRotation();

	while (pollKeyEvents())
	{
		handleKeyEvents();
	}

	mCamera.updateWorldToCameraMatrix();
}

void World::handleKeyEvents()
{
	static bool leftMouseButtonDown = false; // TODO: make own input class

	float change = 2*static_cast<float>(Constants::pi)/8;

	change *= 0.1f;

	switch (mpSdlEvent.type)
	{
	case SDL_KEYDOWN:
	{
		switch (mpSdlEvent.key.keysym.sym)
		{
		case SDLK_w:
			// Handle camera pitch up
			mCamera.mPitch += change;
			mCamera.mPitch = fmod(mCamera.mPitch, 2.0f * static_cast<float>(Constants::pi));
			mCamera.updatePitchMatrix();
			break;

		case SDLK_s:
			// Handle camera pitch down
			mCamera.mPitch -= change;
			mCamera.mPitch = fmod(mCamera.mPitch, 2 * static_cast<float>(Constants::pi));
			mCamera.updatePitchMatrix();
			break;

		case SDLK_a:
			// Handle camera yaw left
			mCamera.mYaw += change;
			mCamera.mYaw = fmod(mCamera.mYaw, 2 * static_cast<float>(Constants::pi));
			mCamera.updateYawMatrix();
			break;

		case SDLK_d:
			// Handle camera yaw right
			mCamera.mYaw -= change;
			mCamera.mYaw = fmod(mCamera.mYaw, 2 * static_cast<float>(Constants::pi));
			mCamera.updateYawMatrix();
			break;

		case SDLK_q:
			// Handle camera roll left
			mCamera.mRoll -= change;
			mCamera.mRoll = fmod(mCamera.mRoll, 2 * static_cast<float>(Constants::pi));
			mCamera.updateRollMatrix();
			break;

		case SDLK_e:
			// Handle camera roll right
			mCamera.mRoll += change;
			mCamera.mRoll = fmod(mCamera.mRoll, 2 * static_cast<float>(Constants::pi));
			mCamera.updateRollMatrix();
			break;

		case SDLK_r:
			resetScene();
			break;
		}
		break;
	}
	case SDL_MOUSEBUTTONDOWN:
	{
		if (mpSdlEvent.button.button == SDL_BUTTON_LEFT)
		{
			leftMouseButtonDown = true;
			mMousePrevX = mpSdlEvent.button.x;
			mMousePrevY = mpSdlEvent.button.y;
			if (mButtonReset.isClicked(mpSdlEvent.button.x, mpSdlEvent.button.y))
			{
				std::string output = "Button clicked.\n";

				OutputDebugStringA(output.c_str());
				resetScene();
			}
		}
		break;
	}
	case SDL_MOUSEBUTTONUP:
	{
		if (mpSdlEvent.button.button == SDL_BUTTON_LEFT)
		{
			leftMouseButtonDown = false;
		}
		break;
	}
	case SDL_MOUSEMOTION:
	{
		if (leftMouseButtonDown)
		{
			mMouseDiffX = mMousePrevX - mpSdlEvent.button.x;
			mMouseDiffY = mMousePrevY - mpSdlEvent.button.y;

			mMousePrevX = mpSdlEvent.button.x;
			mMousePrevY = mpSdlEvent.button.y;
			
			Vector3Custom<float> translation((static_cast<float>(mMouseDiffX)) / 50, (static_cast<float>(-mMouseDiffY)) / 50, 0);
			mCamera.moveCamera(translation);
		}
		break;
	}
	case SDL_MOUSEWHEEL:
	{
		Vector3Custom<float> translation(0.0f, 0.0f, static_cast<float>(-mpSdlEvent.wheel.y));
		mCamera.moveCamera(translation);
		break;
	}
	default:
		break;
	}
}

void World::resetScene()
{
	mCamera.reset();
}

void World::calculateWorldToCameraMatrix()
{
	mCamera.updateWorldToCameraMatrix();
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

void World::renderButton()
{
	bool inWorld = false;
	TextRenderer::print(mButtonReset.mLabel,
		mButtonReset.mDimensions.mX + mButtonReset.mPosition.mX,
		mButtonReset.mDimensions.mY + mButtonReset.mPosition.mY,
		inWorld);
	UiDrawRectangle(mButtonReset.mDimensions, mButtonReset.mPosition, inWorld);
}

void World::UiDrawRectangle(Vector2Custom<int> dimensions, Vector2Custom<int> position, const bool inWorld)
{
	MediaLayer::getInstance().RenderRect(dimensions.mX, dimensions.mY, position.mX, position.mY, inWorld);
}

void World::renderObjects()
{
	static int k = 0;

	Cube* myC = mObjects[0];

	for (int i = 0; i < mObjectCount; i++)
	{
		myC = mObjects[i];

		renderObject(*mObjects[i]);
	}
}

void World::renderObject(const Cube& cube)
{
	MediaLayer::getInstance().RenderPolygon(cube.mVertices, cube.mIndices, mCamera.mWtcMatrix, true);
}

void World::renderLine(const Vector3Custom<float>& vector1, const Vector3Custom<float>& vector2, const bool inWorld)
{
	MediaLayer::getInstance().RenderLine(vector1, vector2, mCamera.mWtcMatrix, inWorld);
}

void World::renderCoordinateSystem()
{
	const bool inWorld = true;
	renderLine(mCoordinateSystemGrid.mXStart, mCoordinateSystemGrid.mXEnd, inWorld);
	renderLine(mCoordinateSystemGrid.mYStart, mCoordinateSystemGrid.mYEnd, inWorld);
	renderLine(mCoordinateSystemGrid.mZStart, mCoordinateSystemGrid.mZEnd, inWorld);
}

void World::worldMain()
{
	renderCoordinateSystem();
	renderObjects();
	renderButton();

	const bool inWorld = true;

	TextRenderer::print("X: " + std::to_string(mCamera.mCamera.mX), 100, 420, inWorld);
	TextRenderer::print("Y: " + std::to_string(mCamera.mCamera.mY), 100, 440, inWorld);
	TextRenderer::print("Z: " + std::to_string(mCamera.mCamera.mZ), 100, 460, inWorld);
}