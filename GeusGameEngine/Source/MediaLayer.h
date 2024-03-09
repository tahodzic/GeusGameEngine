#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Vector2Custom.h"
#include "Vector3Custom.h"
#include "SdlLibrary.h"


class MediaLayer
{
private:
	MediaLayer();

public:
	MediaLayer(const MediaLayer&) = delete;
	MediaLayer& operator=(const MediaLayer&) = delete;

	static MediaLayer& getInstance();

	std::unique_ptr<SdlLibrary> mpSdlLibrary;

	void Initialize(const std::string_view title,
		const int& windowsPosX, const int& windowsPosY,
		const int& windowWidth, const int& windowHeight,
		const int& canvasWidth, const int& canvasHeight,
		const Matrix44<float>& projectionMatrix);

	void RenderLine(
		const Vector3Custom<float>& vector1,
		const Vector3Custom<float>& vector2,
		const Matrix44<float>& worldToCameraMatrix,
		const bool inWorld) const;

	void RenderPolygon(
		const std::vector<Vector3Custom<float>>& vertices,
		const std::vector<int>& indices,
		const Matrix44<float>& worldToCameraMatrix,
		const Matrix44<float>& localToWorldMatrix,
		const bool inWorld) const;

	void RenderRect(const int width, const int height, const int x, const int y, const bool inWorld) const;

	//void setRenderDrawColor();

	void Render() const;

	void PrepareRenderer() const;

	std::shared_ptr<IRenderer> GetRenderer() const;

	//void renderClear();

	//void createWindow();

	//void initializeFont();

	//void pollEvent();

	void SetRenderViewPort(const bool inWorld) const;

	void SizeUTF8(std::string_view text, int& w, int& h) const;

	void RenderUTF8_Solid(std::string_view text,const uint8_t r,const uint8_t g,const uint8_t b,const uint8_t a) const;

	void CreateTextureFromSurface() const;

	void SetDestRect(const int x, const int y, const int w, const int h) const;

	void RenderCopy() const;

	void FreeSurface() const;

	void DestroyTexture() const;
};

