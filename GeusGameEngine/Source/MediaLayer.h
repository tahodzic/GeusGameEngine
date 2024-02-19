#pragma once

#include <memory>

#include "Vector2Custom.h"
#include "Vector3Custom.h"
#include "IRenderer.h"

#include "IGraphicsLibrary.h"

class MediaLayer
{
private:
	MediaLayer();

public:
	MediaLayer(const MediaLayer&) = delete;
	MediaLayer& operator=(const MediaLayer&) = delete;

	static MediaLayer& getInstance();

	std::unique_ptr<IGraphicsLibrary> mpGraphicsLibrary;

	void initialize(const std::string_view title,
		const int& windowsPosX, const int& windowsPosY,
		const int& windowWidth, const int& windowHeight,
		const int& canvasWidth, const int& canvasHeight,
		const Matrix44<float>& projectionMatrix);

	void renderLine(
		const Vector3Custom<float>& vector1,
		const Vector3Custom<float>& vector2,
		const Matrix44<float>& worldToCameraMatrix);

	void renderTriangle(
		const Vector3Custom<float>& vector1,
		const Vector3Custom<float>& vector2,
		const Vector3Custom<float>& vector3,
		const Matrix44<float>& worldToCameraMatrix);

	//void renderRectangle();

	//void setRenderDrawColor();

	void render();

	void prepareRenderer();

	//void renderClear();

	//void createWindow();

	//void initializeFont();

	//void pollEvent();
};

