#pragma once

#include "State.h"
#include "SubState.h"
#include "Game.h"
#include "SFML\Graphics.hpp"
#include <map>
#include "WorldMap.h"
#include "Defines.h"
#include <vector>

class TileDataBoxState : public SubState
{
private:
	GameDataRef _data;

	sf::Sprite _background;
	sf::Sprite _closeButton;

	std::map<Terrain, double> _terrainData;
	std::map<Terrain, sf::Text> _dataText;

	sf::View _view;

public:
	TileDataBoxState(GameDataRef data, const std::map<Terrain, double> &terrainData);

	virtual void init() override;

	virtual bool handleInput(sf::Event &event) override;
	virtual void update(float delta) override;
	virtual void draw() override;
};