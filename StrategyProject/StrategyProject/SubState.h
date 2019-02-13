#pragma once

#include "State.h"
#include <memory>

class SubState : public State
{
protected:
	bool _remove;

public:
	SubState()
		: _remove(false)
	{
	
	}

	bool remove() { return _remove; }
};

typedef std::unique_ptr<SubState> subStateRef;