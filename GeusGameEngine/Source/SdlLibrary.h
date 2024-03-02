#pragma once

#include "IGraphicsLibrary.h"
#include "Matrix44.h"

#include <string>
#include <memory>


class SdlLibrary
{
private:

public:
	SdlLibrary(std::shared_ptr<IRenderer> rendererControl, std::shared_ptr<IFont> fontControl);
	~SdlLibrary();

	std::shared_ptr<IFont> mpFontHandler;

	std::shared_ptr<IRenderer> mpRendererHandler;

	void Initialize(const std::string_view title,
		const int& windowsPosX, const int& windowsPosY,
		const int& windowWidth, const int& windowHeight,
		const int& canvasWidth, const int& canvasHeight,
		const Matrix44<float>& projectionMatrix);

	static std::unique_ptr<SdlLibrary> CreateAndSetup(const std::string_view title,
		const int& windowsPosX, const int& windowsPosY,
		const int& windowWidth, const int& windowHeight,
		const int& canvasWidth, const int& canvasHeight,
		const Matrix44<float>& projectionMatrix);
};

