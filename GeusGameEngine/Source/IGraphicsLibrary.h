#pragma once

#include "IFont.h"
#include "IRenderer.h"
#include "Matrix44.h"

#include <string>
#include <memory>

class IGraphicsLibrary
{
public:

    virtual void Initialize(const std::string_view title,
        const int& windowsPosX, const int& windowsPosY,
        const int& windowWidth, const int& windowHeight,
        const int& canvasWidth, const int& canvasHeight,
        const Matrix44<float>& projectionMatrix) = 0;

    virtual std::shared_ptr<IFont> GetFontHandler() = 0;

    virtual std::shared_ptr<IRenderer> GetRendererHandler() = 0;

    virtual ~IGraphicsLibrary() {}
};