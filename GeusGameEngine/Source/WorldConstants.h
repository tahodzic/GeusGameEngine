#pragma once

#include "Constants.h"

#include <string>

namespace WorldConstants
{
    constexpr std::string_view windowTitle = "My Gamestudio";

    constexpr int windowPosX = 20;

    constexpr int windowPosY = 100;

    constexpr int windowWidth = 1280;

    constexpr int windowHeight = 720;

    constexpr int canvasWidth = 2;

    constexpr int canvasHeight = 2;

    constexpr float angleOfViewW = 90.0f * (static_cast<float>(Constants::pi) / 180.0f);

    constexpr float angleOfViewH = 120.0f * (static_cast<float>(Constants::pi) / 180.0f);

    constexpr float zNear = 1.0f;

    constexpr float zFar = 1000.0f;

    constexpr  float canvasW = 16.0f;

    constexpr  float canvasH = 9.0f;

    constexpr  float aspectRatio = canvasW / canvasH;

    const float  top = zNear * tan(angleOfViewW / 2.0f);

    const float  bottom = -top;

    const float  right = aspectRatio * top;

    const float  left = -right;

    constexpr int maxObjectsInWorld = 10;
}