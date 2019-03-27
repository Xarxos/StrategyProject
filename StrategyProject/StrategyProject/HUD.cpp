#include "stdafx.h"
#include "HUD.h"
#include "SFML\Graphics.hpp"
#include "Defines.h"
#include "Game.h"

Hud::Hud(EngineDataRef engineData, DatabaseRef gameData)
	: _engine(engineData),
	_database(gameData),
	_view(sf::Vector2f(Define::WORLD_VIEW_WIDTH / 2, Define::WORLD_VIEW_HEIGHT / 2), sf::Vector2f(Define::WORLD_VIEW_WIDTH, Define::WORLD_VIEW_HEIGHT))
{
	
}

void Hud::init()
{
	_engine->assets.loadTexture("HUD Top Shelf", Filepath::HUD_TOP_SHELF);
	_engine->assets.loadTexture("Database Button", Filepath::DATABASE_BUTTON);

	_topShelf.setTexture(_engine->assets.getTexture("HUD Top Shelf"));
	_databaseButton.setTexture(_engine->assets.getTexture("Database Button"));

	_databaseButton.setPosition(Graphics::HUD_DATABASE_BUTTON_POSITION);
}

HUDButton Hud::clickedButton()
{
	if (_engine->input.isSpriteClicked(_databaseButton, sf::Mouse::Left, _engine->window))
	{
		return HUDButton::Database;
	}

	return HUDButton::None;
}

void Hud::draw()
{
	_engine->window.setView(_view);

	_engine->window.draw(_topShelf);
	_engine->window.draw(_databaseButton);
}