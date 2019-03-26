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

class RegionDataBox : public Box
{
private:
	sf::Sprite _enterButton;

	int _regionIndex;
	sf::Vector2i _regionCoords;

public:
	RegionDataBox(EngineDataRef engineData, DatabaseRef database, int regionIndex, sf::Vector2i regionCoords);

	virtual void init() override;

	virtual bool handleInput(sf::Event &event) override;
	virtual void update(float delta) override;
	virtual void draw() override;

	sf::Vector2i getTileCoords() { return _regionCoords; }

private:
	void initRegionData();
};