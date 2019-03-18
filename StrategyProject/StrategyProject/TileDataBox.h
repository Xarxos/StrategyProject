#pragma once

#include "State.h"
#include "SubState.h"
#include "Box.h"
#include "Game.h"
#include "SFML\Graphics.hpp"
#include <map>
#include "WorldMap.h"
#include "Defines.h"
#include <vector>
#include "GameDatabase.h"
#include <initializer_list>

class TileDataBox : public Box
{
private:
	sf::Sprite _enterButton;

	int _tileIndex;
	sf::Vector2i _tileCoords;

public:
	TileDataBox(EngineDataRef engineData, DatabaseRef database, int tileIndex, sf::Vector2i tileCoords);

	virtual void init() override;

	virtual bool handleInput(sf::Event &event) override;
	virtual void update(float delta) override;
	virtual void draw() override;

	sf::Vector2i getTileCoords() { return _tileCoords; }

private:
	void initTileData();
};