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

	sf::Vector2i _tileCoords;
	std::map<Terrain, double> _terrainData;
	std::map<Terrain, sf::Text> _dataText;

	sf::View _view;

	bool _mouseButtonHeld;
	sf::Vector2i _previousMousePos;

public:
	TileDataBoxState(EngineDataRef engineData, DatabaseRef database, sf::Vector2i tileCoords, const std::map<Terrain, double> &terrainData);

	virtual void init() override;

	virtual bool handleInput(sf::Event &event) override;
	virtual void update(float delta) override;
	virtual void draw() override;

	void selectBox(bool isSelected = true);

	sf::Vector2i getTileCoords() { return _tileCoords; }
};