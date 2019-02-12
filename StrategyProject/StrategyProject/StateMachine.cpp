#include "stdafx.h"
#include "StateMachine.h"

void StateMachine::addState(stateRef newState, bool isReplacing)
{
	_isAdding = true;
	_isReplacing = isReplacing;

	_newState = std::move(newState);
}

void StateMachine::removeState()
{
	_isRemoving = true;
}

void StateMachine::processStateChanges()
{
	if (_isRemoving && !_states.empty())
	{
		_states.pop_back();

		if (!_states.empty())
		{
			_states.back()->resumeAll();
		}

		_isRemoving = false;
	}

	if (_isAdding)
	{
		if (!_states.empty())
		{
			if (_isReplacing)
			{
				_states.pop_back();
			}
			else
			{
				//_states.top()->pause();
			}
		}

		_states.push_back(std::move(_newState));
		_states.back()->init();
		_isAdding = false;
	}
}