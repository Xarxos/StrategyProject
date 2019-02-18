#pragma once

#include "State.h"
#include "Game.h"
#include "SFML\Graphics.hpp"
#include "Defines.h"
#include <vector>

class Hud
{
private:
	EngineDataRef _engine;

	sf::View _view;

	sf::Sprite _background;

public:
	Hud(EngineDataRef engineData)
		: _engine(engineData),
		_view(sf::Vector2f(Define::WORLD_VIEW_WIDTH / 2, Define::WORLD_VIEW_HEIGHT / 2), sf::Vector2f(Define::WORLD_VIEW_WIDTH, Define::WORLD_VIEW_HEIGHT))
	{}

	void init();

	void draw();
};