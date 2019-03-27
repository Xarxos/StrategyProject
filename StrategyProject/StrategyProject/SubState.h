#pragma once

#include <memory>
#include "SFML\Graphics.hpp"

class SubState
{
protected:
	bool _remove;
	bool _moveToTop;

public:
	SubState()
		: _remove(false)
	{
	
	}

	virtual void init() = 0;

	virtual bool handleInput(sf::Event &event) = 0;
	virtual void update(float delta) = 0;
	virtual void draw() = 0;

	virtual void pause() {}
	virtual void resume() {}

	bool remove() { return _remove; }
	bool moveToTop() { return _moveToTop; }
	//void disableMoveToTope() { _moveToTop = false; }
};

typedef std::unique_ptr<SubState> subStateRef;