#pragma once

#include <memory>
#include <stack>
#include <vector>

#include "State.h"

typedef std::unique_ptr<State> stateRef;

class StateMachine
{
private:
	std::vector<stateRef> _states;
	stateRef _newState;

	bool _isRemoving;
	bool _isAdding;
	bool _isReplacing;

public:
	StateMachine() {}
	~StateMachine() {}

	void addState(stateRef newState, bool isReplacing = true);
	void removeState();

	void processStateChanges();

	stateRef& getActiveState() { return _states.back(); }
	std::vector<stateRef>& getStateStack() { return _states; }
};