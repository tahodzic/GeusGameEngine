#pragma once

#include <gmock/gmock.h>
#include <memory>
#include <string>
#include <string_view>
#include <vector>
#include "IMediaLayer.h" 
#include "Vector3.h"
#include "Matrix44.h"
#include "IFont.h"
#include "IRenderer.h"


class MediaLayerMock : public IMediaLayer {
public:
    MOCK_METHOD(void, RenderLine,
        (const Vector3<float>& vector1,
            const Vector3<float>& vector2,
            const Matrix44<float>& worldToCameraMatrix,
            const bool inWorld),
        (const, override));

    MOCK_METHOD(void, RenderPolygon,
        (const std::vector<Vector3<float>>& vertices,
            const std::vector<int>& indices,
            const Matrix44<float>& worldToCameraMatrix,
            const Matrix44<float>& localToWorldMatrix,
            const bool inWorld),
        (const, override));

    MOCK_METHOD(void, RenderRect,
        (const int width, const int height, const int x, const int y, const bool inWorld),
        (const, override));

    MOCK_METHOD(void, Render, (), (const, override));

    MOCK_METHOD(void, PrepareRenderer, (), (const, override));

    MOCK_METHOD(std::shared_ptr<IRenderer>, GetRenderer, (), (const, override));

    MOCK_METHOD(std::shared_ptr<IFont>, GetFontHandler, (), (const, override));

    MOCK_METHOD(void, SetRenderViewPort, (const bool inWorld), (const, override));

    MOCK_METHOD(void, SizeUTF8, (std::string_view text, int& w, int& h), (const, override));

    MOCK_METHOD(void, RenderUTF8_Solid,
        (std::string_view text, const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a),
        (const, override));

    MOCK_METHOD(void, CreateTextureFromSurface, (), (const, override));

    MOCK_METHOD(void, SetDestRect, (const int x, const int y, const int w, const int h), (const, override));

    MOCK_METHOD(void, RenderCopy, (), (const, override));

    MOCK_METHOD(void, FreeSurface, (), (const, override));

    MOCK_METHOD(void, DestroyTexture, (), (const, override));
};
