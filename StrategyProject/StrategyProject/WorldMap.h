#pragma once

#include "Game.h"
#include "SFML\Graphics.hpp"
#include "State.h"
#include "SubState.h"
#include <vector>
#include <map>
#include <list>

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
	std::map<Terrain, std::vector<double>> _tileTerrainRatios;
	sf::Texture _backgroundTexture;
	sf::Image _terrainData;

	sf::View _view;

	std::list<subStateRef> _subStates;

public:
	WorldMap(GameDataRef data);

	virtual void init() override;

	virtual void handleInput() override;
	virtual void update(float delta) override;
	virtual void draw() override;

private:
	void loadAssets();
	void initializeTile(int tileX, int tileY);
	void loadTerrainData();
	void loadTerrainDataForTile(int tileX, int tileY);

	void handleMousePressEvent(sf::Event &event);
	void handleMouseScrollEvent(sf::Event &event);
	void handleKeyPressEvent(sf::Event &event);
	void handleRealTimeKeyPressInput();
	
	void changeMapMode(Terrain mapMode);
	int coordsToTile(sf::Vector2i worldCoords);
};