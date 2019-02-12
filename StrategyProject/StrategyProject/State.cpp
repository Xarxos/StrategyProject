#include "stdafx.h"
#include "State.h"

void State::pause(bool pause)
{
	_isPaused = pause;
}

void State::hide(bool hide)
{
	_isHidden = hide;
}

void State::freezeInput(bool freezeInput)
{
	_inputFrozen = freezeInput;
}

void State::resumeAll()
{
	_isPaused = false;
	_isHidden = false;
	_inputFrozen = false;
}