#pragma once

#include "State.h"
#include "Game.h"
#include "SFML\Graphics.hpp"

class MainMenuState : public State
{
private:
	EngineDataRef _engine;

	sf::Sprite _background;
	sf::Sprite _testGameButton;
	sf::Sprite _exitButton;

public:
	MainMenuState(EngineDataRef data) : _engine(data)
	{}

	virtual void init() override;

	virtual void handleInput() override;
	virtual void update(float delta) override;
	virtual void draw() override;
};