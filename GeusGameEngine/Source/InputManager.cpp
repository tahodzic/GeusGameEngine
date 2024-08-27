#include "InputManager.h"

#include <SDL.h>

static void TranslateKeyCode(const SDL_Event& sdlEvent, InputManager::InputEvent& inputEvent)
{
    switch (sdlEvent.key.keysym.sym)
    {
    case SDLK_r:
        inputEvent.keyCode = InputManager::KeyCode::KeyR;
        break;
    case SDLK_m:
        inputEvent.keyCode = InputManager::KeyCode::KeyM;
        break;
    default:
        break;
    }
}

static void TranslateKeyCodeDown(const SDL_Event& sdlEvent, InputManager::InputEvent& inputEvent)
{
    inputEvent.type = InputManager::EventType::KeyPress;
    TranslateKeyCode(sdlEvent, inputEvent);
}

static void TranslateKeyCodeUp(const SDL_Event& sdlEvent, InputManager::InputEvent& inputEvent)
{
    inputEvent.type = InputManager::EventType::KeyRelease;
    TranslateKeyCode(sdlEvent, inputEvent);
}

static void TranslateMouseEvent(const SDL_Event& sdlEvent, InputManager::InputEvent& inputEvent)
{
    switch (sdlEvent.button.button)
    {
    case SDL_BUTTON_LEFT:
        inputEvent.keyCode = InputManager::KeyCode::MouseLeft;
        break;
    case SDL_BUTTON_RIGHT:
        inputEvent.keyCode = InputManager::KeyCode::MouseRight;
        break;
    default:
        break;
    }

    inputEvent.mouseX = sdlEvent.button.x;
    inputEvent.mouseY = sdlEvent.button.y;
}

static void TranslateMouseEventDown(const SDL_Event& sdlEvent, InputManager::InputEvent& inputEvent)
{
    inputEvent.type = InputManager::EventType::MousePress;
    TranslateMouseEvent(sdlEvent, inputEvent);
}

static void TranslateMouseEventUp(const SDL_Event& sdlEvent, InputManager::InputEvent& inputEvent)
{
    inputEvent.type = InputManager::EventType::MouseRelease;
    TranslateMouseEvent(sdlEvent, inputEvent);
}

static void TranslateMouseMotion(const SDL_Event& sdlEvent, InputManager::InputEvent& inputEvent)
{
    inputEvent.type = InputManager::EventType::MouseMove;
    inputEvent.mouseX = sdlEvent.motion.x;
    inputEvent.mouseY = sdlEvent.motion.y;
}

static void TranslateMouseWheel(const SDL_Event& sdlEvent, InputManager::InputEvent& inputEvent)
{
    inputEvent.type = InputManager::EventType::MouseWheel;
    inputEvent.mouseWheelY = sdlEvent.wheel.y;
}

static InputManager::InputEvent TranslateEvent(const SDL_Event& sdlEvent)
{
    InputManager::InputEvent inputEvent;

    switch (sdlEvent.type)
    {
    case SDL_KEYDOWN:
        TranslateKeyCodeDown(sdlEvent, inputEvent);
        break;
    case SDL_KEYUP:
        TranslateKeyCodeUp(sdlEvent, inputEvent);
        break;
    case SDL_MOUSEBUTTONDOWN:
        TranslateMouseEventDown(sdlEvent, inputEvent);
        break;
    case SDL_MOUSEBUTTONUP:
        TranslateMouseEventUp(sdlEvent, inputEvent);
        break;
    case SDL_MOUSEMOTION:
        TranslateMouseMotion(sdlEvent, inputEvent);
        break;
    case SDL_MOUSEWHEEL:
        TranslateMouseWheel(sdlEvent, inputEvent);
        break;
    default:
        break;
    }

    return inputEvent;
}

void InputManager::HandleEvent(const InputEvent& inputEvent)
{
    auto it = mEventHandlers.find(inputEvent.type);

    if (it != mEventHandlers.end())
    {
        it->second(inputEvent);
    }
    else
    {
        // todo
    }
}

void InputManager::UpdateState(const InputEvent& inputEvent)
{
    switch (inputEvent.type)
    {
    case EventType::MousePress:
    {
        if (inputEvent.keyCode == KeyCode::MouseLeft)
        {
            
            mInputState.leftMouseButtonDown = true;
            mInputState.prevMouseX = inputEvent.mouseX;
            mInputState.prevMouseY = inputEvent.mouseY;
        }
        if (inputEvent.keyCode == KeyCode::MouseRight)
        {
            mInputState.rightMouseButtonDown = true;
            mInputState.prevMouseX = inputEvent.mouseX;
            mInputState.prevMouseY = inputEvent.mouseY;
        }
        break;
    }
    case EventType::MouseRelease:
    {
        if (inputEvent.keyCode == KeyCode::MouseLeft)
        {
            mInputState.leftMouseButtonDown = false;
        }
        if (inputEvent.keyCode == KeyCode::MouseRight)
        {
            mInputState.rightMouseButtonDown = false;
        }
        break;
    }
    default:
        break;
    }
}

//void World::UpdateInputState(const InputEvent& event, InputState& inputState)
//{
//    switch (event.type)
//    {
//    case EventType::MousePress:
//        if (event.keyCode == KeyCode::MouseLeft) {
//            inputState.leftMouseButtonDown = true;
//        }
//        else if (event.keyCode == KeyCode::MouseRight) {
//            inputState.rightMouseButtonDown = true;
//        }
//        break;
//
//    case EventType::MouseRelease:
//        if (event.keyCode == KeyCode::MouseLeft) {
//            inputState.leftMouseButtonDown = false;
//        }
//        else if (event.keyCode == KeyCode::MouseRight) {
//            inputState.rightMouseButtonDown = false;
//        }
//        break;
//
//    case EventType::MouseMove:
//        inputState.mouseX = event.mouseX;
//        inputState.mouseY = event.mouseY;
//
//        if (inputState.leftMouseButtonDown) {
//            // Calculate the difference from the last position
//            int diffX = inputState.mouseX - inputState.prevMouseX;
//            int diffY = inputState.mouseY - inputState.prevMouseY;
//
//            // Use diffX and diffY to rotate the camera, for example
//            RotateCamera(diffX, diffY);
//        }
//
//        // Update previous mouse position at the end of the move event handling
//        inputState.updatePrevPosition();
//        break;
//
//        // Handle other event types...
//    }
//}


void InputManager::HandleInput()
{
    SDL_Event sdlEvent;

    if (!SDL_PollEvent(&sdlEvent))
    {
        return;
    }

    InputManager::InputEvent inputEvent = TranslateEvent(sdlEvent);

    UpdateState(inputEvent);

    HandleEvent(inputEvent);
}

//void InputManager::RegisterEventHandlers(EventHandlers eventHandlers)
//{
//    mEventHandlers = eventHandlers;
//}

void InputManager::SetCurrentState(WorldState::State state)
{
    mCurrentState = state;
}

void InputManager::RegisterHandler(EventType type, EventHandlerType handler)
{
    mEventHandlers[type] = handler;
}