#include "InputManager.h"

#include <SDL.h>

static void TranslateKeyCode(const SDL_Event& sdlEvent, InputTypes::InputEvent& inputEvent)
{
    switch (sdlEvent.key.keysym.sym)
    {
    case SDLK_r:
        inputEvent.keyCode = InputTypes::KeyCode::KeyR;
        break;
    case SDLK_m:
        inputEvent.keyCode = InputTypes::KeyCode::KeyM;
        break;
    default:
        break;
    }
}

static void TranslateKeyCodeDown(const SDL_Event& sdlEvent, InputTypes::InputEvent& inputEvent)
{
    inputEvent.type = InputTypes::EventType::KeyPress;
    TranslateKeyCode(sdlEvent, inputEvent);
}

static void TranslateKeyCodeUp(const SDL_Event& sdlEvent, InputTypes::InputEvent& inputEvent)
{
    inputEvent.type = InputTypes::EventType::KeyRelease;
    TranslateKeyCode(sdlEvent, inputEvent);
}

static void TranslateMouseEvent(const SDL_Event& sdlEvent, InputTypes::InputEvent& inputEvent)
{
    switch (sdlEvent.button.button)
    {
    case SDL_BUTTON_LEFT:
        inputEvent.keyCode = InputTypes::KeyCode::MouseLeft;
        break;
    case SDL_BUTTON_RIGHT:
        inputEvent.keyCode = InputTypes::KeyCode::MouseRight;
        break;
    default:
        break;
    }

    inputEvent.mouseX = sdlEvent.button.x;
    inputEvent.mouseY = sdlEvent.button.y;
}

static void TranslateMouseEventDown(const SDL_Event& sdlEvent, InputTypes::InputEvent& inputEvent)
{
    inputEvent.type = InputTypes::EventType::MousePress;
    TranslateMouseEvent(sdlEvent, inputEvent);
}

static void TranslateMouseEventUp(const SDL_Event& sdlEvent, InputTypes::InputEvent& inputEvent)
{
    inputEvent.type = InputTypes::EventType::MouseRelease;
    TranslateMouseEvent(sdlEvent, inputEvent);
}

static void TranslateMouseMotion(const SDL_Event& sdlEvent, InputTypes::InputEvent& inputEvent)
{
    inputEvent.type = InputTypes::EventType::MouseMove;
    inputEvent.mouseX = sdlEvent.motion.x;
    inputEvent.mouseY = sdlEvent.motion.y;
}

static void TranslateMouseWheel(const SDL_Event& sdlEvent, InputTypes::InputEvent& inputEvent)
{
    inputEvent.type = InputTypes::EventType::MouseWheel;
    inputEvent.mouseWheelY = sdlEvent.wheel.y;
}

static InputTypes::InputEvent TranslateEvent(const SDL_Event& sdlEvent)
{
    InputTypes::InputEvent inputEvent;

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


InputManager::InputManager()
{
}

InputManager::~InputManager()
{
}


void InputManager::HandleEvent(const InputTypes::InputEvent& inputEvent)
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

void InputManager::UpdateState(const InputTypes::InputEvent& inputEvent)
{
    switch (inputEvent.type)
    {
    case InputTypes::EventType::MousePress:
    {
        if (inputEvent.keyCode == InputTypes::KeyCode::MouseLeft)
        {
            
            mInputState.leftMouseButtonDown = true;
            mInputState.prevMouseX = inputEvent.mouseX;
            mInputState.prevMouseY = inputEvent.mouseY;
        }
        if (inputEvent.keyCode == InputTypes::KeyCode::MouseRight)
        {
            mInputState.rightMouseButtonDown = true;
            mInputState.prevMouseX = inputEvent.mouseX;
            mInputState.prevMouseY = inputEvent.mouseY;
        }
        break;
    }
    case InputTypes::EventType::MouseRelease:
    {
        if (inputEvent.keyCode == InputTypes::KeyCode::MouseLeft)
        {
            mInputState.leftMouseButtonDown = false;
        }
        if (inputEvent.keyCode == InputTypes::KeyCode::MouseRight)
        {
            mInputState.rightMouseButtonDown = false;
        }
        break;
    }
    default:
        break;
    }
}

void InputManager::HandleInput()
{
    SDL_Event sdlEvent;

    if (!SDL_PollEvent(&sdlEvent))
    {
        return;
    }

    InputTypes::InputEvent inputEvent = TranslateEvent(sdlEvent);

    if (inputEvent.type == InputTypes::EventType::None)
    {
        return;
    }

    mInputEvent = inputEvent;

    UpdateState(inputEvent);

    NotifyObservers();
}

void InputManager::AddObserver(IInputObserver& observer)
{
    mObservers.push_back(observer);
    //mObservers.push_back(&observer);
}

void InputManager::NotifyObservers()
{
    for (auto observer : mObservers)
    {
        observer.get().Update(mInputEvent, mInputState);
    }
}

void InputManager::SetCurrentState(WorldState::State state)
{
    mCurrentState = state;
}

void InputManager::RegisterHandler(InputTypes::EventType type, InputTypes::EventHandlerType handler)
{
    mEventHandlers[type] = handler;
}