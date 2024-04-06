#pragma once

#include "WorldState.h"

#include <functional>
#include <map>

class InputManager
{
public:
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

private:
    std::map<EventType, EventHandlerType> mEventHandlers;

    WorldState::State mCurrentState;

    void HandleEvent(const InputEvent& inputEvent);

    void UpdateState(const InputEvent& inputEvent);


public:
    InputState mInputState;

    void RegisterHandler(EventType type, EventHandlerType handler);

    //void RegisterEventHandlers(EventHandlers eventHandlers);

    void SetCurrentState(WorldState::State state);

    void HandleInput();
};

