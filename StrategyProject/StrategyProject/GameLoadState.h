#pragma once

#include "State.h"
#include "Game.h"
#include "SFML\Graphics.hpp"
#include "GameDatabase.h"

class GameLoadState : public State
{
private:
	EngineDataRef _engine;
	DatabaseRef _database = std::make_shared<Database>();

	sf::Clock _clock;

public:
	GameLoadState(EngineDataRef engineData) : _engine(engineData)
	{}

	virtual void init() override;

	virtual void handleInput() override;
	virtual void update(float delta) override;
	virtual void draw() override;

private:
	void loadMineralTypeData();
	void loadStoneTypeData();
	void calculateStoneProperties(int stoneTypeIndex);
	void loadRegionData();
	void loadTileData(int regionIndex);
	void calculateRegionData(int regionIndex);

	void printData();

	std::string generateName();
};