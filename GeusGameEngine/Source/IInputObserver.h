#pragma once

#include "InputTypes.h"

class IInputObserver
{
public:
	virtual ~IInputObserver() {}

	virtual void Update(const InputTypes::InputEvent& event, [[maybe_unused]]const InputTypes::InputState& state) = 0;
};