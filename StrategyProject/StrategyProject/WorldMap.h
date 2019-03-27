#pragma once

#include <vector>
#include <map>
#include <list>

#include "Game.h"
#include "SFML\Graphics.hpp"
#include "State.h"
#include "SubState.h"
#include "HUD.h"
#include "GameDatabase.h"

class WorldMap : public State
{
private:
	EngineDataRef _engine;
	DatabaseRef _database;

	sf::VertexArray _vertices;
	sf::Texture _backgroundTexture;
	Hud _HUD;
	sf::RectangleShape _selectedTile;
	bool _tileIsSelected;

	std::vector<std::vector<int>> _tileMatrix;

	sf::View _mainView;
	sf::View _miniMapView;

	std::list<subStateRef> _subStates;

public:
	WorldMap(EngineDataRef engineData, DatabaseRef database);

	virtual void init() override;

	virtual void handleInput() override;
	virtual void update(float delta) override;
	virtual void draw() override;

private:
	void loadAssets();
	void initializeTile(int tileX, int tileY);

	void handleMousePressEvent(sf::Event &event);
	void handleMouseScrollEvent(sf::Event &event);
	void handleKeyPressEvent(sf::Event &event);
	void handleRealTimeKeyPressInput();

	void updateHUD(float delta);
	void updateSubStates(float delta);
	void checkTileSelection();
	void correctCameraView();
	
	//void changeMapMode(Terrain mapMode);
	sf::Vector2i coordsToTile(sf::Vector2i worldCoords);
};