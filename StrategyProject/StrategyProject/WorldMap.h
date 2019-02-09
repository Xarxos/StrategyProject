#pragma once

#include "Game.h"
#include "SFML\Graphics.hpp"
#include "State.h"
#include <vector>

class WorldMap : public State
{
private:
	GameDataRef _data;

	sf::VertexArray _vertices;
	std::vector<std::vector<int>> _tileMatrix;

public:
	WorldMap(GameDataRef data);

	virtual void init() override;

	virtual void handleInput() override;
	virtual void update(float delta) override;
	virtual void draw() override;
};