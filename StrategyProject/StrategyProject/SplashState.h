#pragma once

#include "State.h"
#include "Game.h"
#include "SFML\Graphics.hpp"

class SplashState : public State
{
private:
	EngineDataRef _engine;
	sf::Clock _clock;

	sf::Sprite _background;
	sf::Sprite _logo;

public:
	SplashState(EngineDataRef engineData) : _engine(engineData)
	{}

	virtual void init() override;

	virtual void handleInput() override;
	virtual void update(float delta) override;
	virtual void draw() override;
};