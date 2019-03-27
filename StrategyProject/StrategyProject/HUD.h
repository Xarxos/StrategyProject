#pragma once

#include "SFML\Graphics.hpp"
#include "Game.h"
#include "GameDatabase.h"

enum class HUDButton
{
	None = -1,
	Database
};

class Hud
{
private:
	EngineDataRef _engine;
	DatabaseRef _database;

	sf::Sprite _topShelf;
	sf::Sprite _databaseButton;

	sf::View _view;

public:
	Hud(EngineDataRef engineData, DatabaseRef gameData);

	void init();

	HUDButton clickedButton();
	sf::FloatRect getBounds() { return _topShelf.getGlobalBounds(); }

	void draw();
};