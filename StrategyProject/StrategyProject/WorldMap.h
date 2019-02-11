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

enum class Terrain
{
	Default = -1,
	Water,
	FlatGround,
	Hills,
	Mountains,
	Forest
};

class WorldMap : public State
{
private:
	GameDataRef _data;

	sf::VertexArray _vertices;
	std::vector<std::vector<int>> _tileMatrix;
	std::map<Terrain, std::vector<double>> _tileTerrains;
	sf::Texture _backgroundTexture;
	sf::Image _terrainData;

	sf::View _view;

public:
	WorldMap(GameDataRef data);

	virtual void init() override;

	virtual void handleInput() override;
	virtual void update(float delta) override;
	virtual void draw() override;

private:
	void loadTerrainData();
	//int terrainPixelsInTile(int tileX, int tileY, Terrain terrain);
	void changeMapMode(Terrain mapMode);
};