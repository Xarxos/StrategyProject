#include "stdafx.h"
#include "HUD.h"
#include "SFML\Graphics.hpp"
#include "Defines.h"
#include "Game.h"

Hud::Hud(GameDataRef data)
	: _data(data),
	_view(sf::Vector2f(Define::WORLD_VIEW_WIDTH / 2, Define::WORLD_VIEW_HEIGHT / 2), sf::Vector2f(Define::WORLD_VIEW_WIDTH, Define::WORLD_VIEW_HEIGHT))
{
	
}

void Hud::init()
{
	_data->assets.loadTexture("HUD Background", Filepath::HUD_BACKGROUND);

	_background.setTexture(_data->assets.getTexture("HUD Background"));
}

void Hud::draw()
{
	_data->window.setView(_view);

	_data->window.draw(_background);
}