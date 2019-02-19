#pragma once

#include "SFML\Graphics.hpp"
#include "Game.h"

class Hud
{
private:
	GameDataRef _data;

	sf::Sprite _background;

	sf::View _view;

public:
	Hud(GameDataRef data);

	void init();

	void draw();
};