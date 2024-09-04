#pragma once

#include <functional>

namespace InputTypes
{
    enum class EventType { KeyPress, KeyRelease, MousePress, MouseRelease, MouseMove, MouseWheel, None };

    enum class KeyCode { KeyR, KeyM, MouseLeft, MouseRight, Unknown };

    struct InputEvent
    {
        EventType type = EventType::None;
        KeyCode keyCode = KeyCode::Unknown;
        int mouseX = 0;
        int mouseY = 0;
        bool leftMouseButtonDown = false;
        bool rightMouseButtonDown = false;
        int mouseWheelY = 0;
    };

    //struct EventHandlers
    //{
    //    std::function<void(const InputEvent&)> keyPress;
    //    std::function<void(const InputEvent&)> keyRelease;
    //    std::function<void(const InputEvent&)> mousePress;
    //    std::function<void(const InputEvent&)> mouseRelease;
    //    std::function<void(const InputEvent&)> mouseMove;
    //    std::function<void(const InputEvent&)> mouseWheel;
    //    WorldState::State state;
    //};

    typedef std::function<void(const InputEvent&)> EventHandlerType;

    struct InputState
    {
        bool leftMouseButtonDown = false;
        bool rightMouseButtonDown = false;
        int mouseX = 0;
        int mouseY = 0;
        int prevMouseX = 0;
        int prevMouseY = 0;

        void updatePrevPosition()
        {
            prevMouseX = mouseX;
            prevMouseY = mouseY;
        }
    };
}