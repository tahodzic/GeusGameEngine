#pragma once

#include "InputTypes.h"
#include "IInputObservable.h"
#include "IInputObserver.h"
#include "WorldState.h"

#include <functional>
#include <map>

class InputManager : public IInputObservable
{
public:
    InputManager();
    ~InputManager();

private:
    std::map<InputTypes::EventType, InputTypes::EventHandlerType> mEventHandlers;

    WorldState::State mCurrentState;

    void HandleEvent(const InputTypes::InputEvent& inputEvent);

    void UpdateState(const InputTypes::InputEvent& inputEvent);


public:
    //std::vector<IInputObserver*> mObservers;
    std::vector<std::reference_wrapper<IInputObserver>> mObservers;

    InputTypes::InputState mInputState;

    InputTypes::InputEvent mInputEvent;

    void RegisterHandler(InputTypes::EventType type, InputTypes::EventHandlerType handler);

    void SetCurrentState(WorldState::State state);

    void HandleInput();

    void AddObserver(IInputObserver& observer) override;

    void NotifyObservers() override;
};

