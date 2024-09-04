#pragma once

#include "IInputObserver.h"

class IInputObservable
{
public:
	virtual ~IInputObservable() {}
	virtual void AddObserver(IInputObserver& observer) = 0;
	virtual void NotifyObservers() = 0;
};