#pragma once

#include <list>
#include "SubState.h"

class State
{
protected:
	std::list<subStateRef> _subStates;

public:
	virtual void init() = 0;

	virtual void handleInput() = 0;
	virtual void update( float delta ) = 0;
	virtual void draw() = 0;

	virtual void pause() {}
	virtual void resume() {}

	virtual std::list<subStateRef>& getSubStates() { return _subStates; }
};