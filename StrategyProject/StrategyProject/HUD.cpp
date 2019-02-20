#include "stdafx.h"
#include "HUD.h"
#include "SFML\Graphics.hpp"
#include "Defines.h"
#include "Game.h"

Hud::Hud(EngineDataRef engineData)
	: _engine(engineData),
	_view(sf::Vector2f(Define::WORLD_VIEW_WIDTH / 2, Define::WORLD_VIEW_HEIGHT / 2), sf::Vector2f(Define::WORLD_VIEW_WIDTH, Define::WORLD_VIEW_HEIGHT))
{
	
}

void Hud::init()
{
	_engine->assets.loadTexture("HUD Background", Filepath::HUD_BACKGROUND);

	_background.setTexture(_engine->assets.getTexture("HUD Background"));
}

void Hud::draw()
{
	_engine->window.setView(_view);

	_engine->window.draw(_background);
}