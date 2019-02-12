#pragma once

class State
{
private:
	bool _isPaused = false;
	bool _isHidden = false;
	bool _inputFrozen = false;

public:
	virtual void init() = 0;

	virtual void handleInput() = 0;
	virtual void update( float delta ) = 0;
	virtual void draw() = 0;

	virtual void pause(bool pause);
	virtual void hide(bool hide);
	virtual void freezeInput(bool freezeInput);
	virtual void resumeAll();

	virtual bool isPaused() { return _isPaused; }
	virtual bool isHidden() { return _isHidden; }
	virtual bool inputFrozen() { return _inputFrozen; }
};