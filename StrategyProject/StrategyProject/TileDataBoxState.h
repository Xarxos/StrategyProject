#pragma once

#include "State.h"
#include "SubState.h"
#include "Game.h"
#include "SFML\Graphics.hpp"
#include <map>
#include "WorldMap.h"
#include "Defines.h"
#include <vector>
#include "GameDatabase.h"

class TileDataBoxState : public SubState
{
private:
	EngineDataRef _engine;
	DatabaseRef _database;

	sf::Sprite _background;
	sf::Sprite _closeButton;
	sf::Sprite _enterButton;

	int _tileIndex;
	sf::Vector2i _tileCoords;

	sf::View _view;

	bool _boxPressed;
	sf::Vector2i _previousMousePos;

public:
	TileDataBoxState(EngineDataRef engineData, DatabaseRef database, int tileIndex, sf::Vector2i tileCoords);

	virtual void init() override;

	virtual bool handleInput(sf::Event &event) override;
	virtual void update(float delta) override;
	virtual void draw() override;

	void selectBox(bool isSelected = true);

	sf::Vector2i getTileCoords() { return _tileCoords; }
};