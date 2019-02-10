#pragma once

#include "Game.h"
#include "SFML\Graphics.hpp"
#include "State.h"
#include <vector>
#include <map>

/*struct TileMap
{
	std::vector<double> flatGround;
	std::vector<double> hills;
	std::vector<double> mountains;
	std::vector<double> water;
	std::vector<double> forest;
	std::vector<double> grassLand;
	std::vector<double> farmLand;
};*/

enum class MapMode
{
	Default = -1,
	Water,
	FlatGround
};

class WorldMap : public State
{
private:
	GameDataRef _data;

	sf::VertexArray _vertices;
	std::vector<std::vector<int>> _tileMatrix;
	std::map<MapMode, std::vector<double>> _tileTerrains;
	sf::Texture _backgroundTexture;

	sf::View _view;

public:
	WorldMap(GameDataRef data);

	virtual void init() override;

	virtual void handleInput() override;
	virtual void update(float delta) override;
	virtual void draw() override;

private:
	void changeMapMode(MapMode mode);
};