#pragma once

#include "SFML\Graphics.hpp"
#include "Game.h"

class Hud
{
private:
	EngineDataRef _engine;

	sf::Sprite _background;

	sf::View _view;

public:
	Hud(EngineDataRef engineData);

	void init();

	void draw();
};