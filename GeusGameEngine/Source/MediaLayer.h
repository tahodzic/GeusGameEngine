#pragma once

#include <memory>

#include "Vector2Custom.h"
#include "Vector3Custom.h"
#include "SdlLibrary.h"
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

	std::unique_ptr<SdlLibrary> mpSdlLibrary;

	void initialize(const std::string_view title,
		const int& windowsPosX, const int& windowsPosY,
		const int& windowWidth, const int& windowHeight,
		const int& canvasWidth, const int& canvasHeight,
		const Matrix44<float>& projectionMatrix);

	void renderLine(
		const Vector3Custom<float>& vector1,
		const Vector3Custom<float>& vector2,
		const Matrix44<float>& worldToCameraMatrix,
		const bool inWorld);

	void renderPolygon(
		const std::vector<Vector3Custom<float>>& vertices,
		const std::vector<int>& indices,
		const Matrix44<float>& worldToCameraMatrix,
		const bool inWorld);

	//void setRenderDrawColor();

	void render();

	void prepareRenderer();

	//void renderClear();

	//void createWindow();

	//void initializeFont();

	//void pollEvent();
};

