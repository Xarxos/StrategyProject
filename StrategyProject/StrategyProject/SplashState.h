#pragma once

#include "State.h"
#include "Game.h"
#include "SFML\Graphics.hpp"

class SplashState : public State
{
private:
	GameDataRef _data;

	sf::Sprite _background;
	sf::Sprite _logo;

public:
	SplashState(GameDataRef data) : _data(data)
	{}

	virtual void init() override;

	virtual void handleInput() override;
	virtual void update(float delta) override;
	virtual void draw() override;
};