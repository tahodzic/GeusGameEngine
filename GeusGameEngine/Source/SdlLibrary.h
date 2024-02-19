#pragma once

#include "IGraphicsLibrary.h"
#include "Matrix44.h"

#include <string>
#include <memory>

class SdlLibraryImpl;

class SdlLibrary : public IGraphicsLibrary
{
private:
	std::unique_ptr<SdlLibraryImpl> mpSdlLibraryImpl;

public:
	SdlLibrary();
	~SdlLibrary();

	std::shared_ptr<IFont> mpFontHandler;

	std::shared_ptr<IRenderer> mpRendererHandler;

	void Initialize(const std::string_view title,
		const int& windowsPosX, const int& windowsPosY,
		const int& windowWidth, const int& windowHeight,
		const int& canvasWidth, const int& canvasHeight,
		const Matrix44<float>& projectionMatrix) override;

	std::shared_ptr<IFont> GetFontHandler() override;

	std::shared_ptr<IRenderer> GetRendererHandler() override;

};

