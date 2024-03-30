#pragma once

#include "Vector2.h"
#include "Vector3.h"
#include "IFont.h"
#include "IRenderer.h"
#include "IMediaLayer.h"

#include <memory>
#include <string>
#include <vector>

class MediaLayer : public IMediaLayer
{
private:

public:
	MediaLayer(std::shared_ptr<IRenderer> rendererHandler, std::shared_ptr<IFont> fontHandler);

	~MediaLayer();

	std::shared_ptr<IFont> mFontHandler;

	std::shared_ptr<IRenderer> mRendererHandler;

	static std::shared_ptr<MediaLayer> CreateAndSetup(const std::string_view title,
		const int& windowsPosX, const int& windowsPosY,
		const int& windowWidth, const int& windowHeight,
		const int& canvasWidth, const int& canvasHeight);

	void RenderLine(
		const Vector3<float>& vector1,
		const Vector3<float>& vector2,
		const Matrix44<float>& worldToCameraMatrix,
		const bool inWorld) const override;

	void RenderPolygon(
		const std::vector<Vector3<float>>& vertices,
		const std::vector<int>& indices,
		const Matrix44<float>& worldToCameraMatrix,
		const Matrix44<float>& localToWorldMatrix,
		const bool inWorld) const override;

	void RenderRect(const int width, const int height, const int x, const int y, const bool inWorld) const override;

	//void setRenderDrawColor();

	void Render() const override;

	void PrepareRenderer() const override;

	std::shared_ptr<IRenderer> GetRenderer() const override;

	std::shared_ptr<IFont> GetFontHandler() const override;

	//void renderClear();

	//void createWindow();

	//void initializeFont();

	//void pollEvent();

	void SetRenderViewPort(const bool inWorld) const override;

	void SizeUTF8(std::string_view text, int& w, int& h) const override;

	void RenderUTF8_Solid(std::string_view text,const uint8_t r,const uint8_t g,const uint8_t b,const uint8_t a) const override;

	void CreateTextureFromSurface() const override;

	void SetDestRect(const int x, const int y, const int w, const int h) const override;

	void RenderCopy() const override;

	void FreeSurface() const override;

	void DestroyTexture() const override;
};