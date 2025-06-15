#pragma once

#include "IFont.h"
#include "IRenderer.h"
#include "Matrix44.h"
#include "Vector3.h"
#include <memory>
#include <string>


class IMediaLayer
{
public:
	virtual ~IMediaLayer() {}
	
	virtual void RenderLine(
		const Vector3<float>& vector1,
		const Vector3<float>& vector2,
		const Matrix44<float>& worldToCameraMatrix,
		const bool inWorld) const = 0;

	virtual void RenderPolygon(
		const std::vector<Vector3<float>>& vertices,
		const std::vector<int>& indices,
		const Matrix44<float>& worldToCameraMatrix,
		const Matrix44<float>& localToWorldMatrix,
		const bool inWorld) const = 0;

	virtual void RenderRect(const int width, const int height, const int x, const int y, const bool inWorld) const = 0;

	//void setRenderDrawColor();

	virtual void Render() const = 0;

	virtual void PrepareRenderer() const = 0;

	virtual std::shared_ptr<IRenderer> GetRenderer() const = 0;

	virtual std::shared_ptr<IFont> GetFontHandler() const = 0;

	//void renderClear();

	//void createWindow();

	//void initializeFont();

	//void pollEvent();

	virtual void SetRenderViewPort(const bool inWorld) const = 0;

	virtual void SizeUTF8(std::string_view text, int& w, int& h) const = 0;

	virtual void RenderUTF8_Solid(std::string_view text, const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a) const = 0;

	virtual void CreateTextureFromSurface() const = 0;

	virtual void SetDestRect(const int x, const int y, const int w, const int h) const = 0;

	virtual void RenderCopy() const = 0;

	virtual void FreeSurface() const = 0;

	virtual void DestroyTexture() const = 0;
};

