#include "stdafx.h"
#include "GameLoadState.h"
#include "Defines.h"
#include "WorldMap.h"
#include "Stone.h"

#include <memory>

void GameLoadState::init()
{
	_database->mineralTypes.push_back(std::make_shared<MineralType>());
	_database->mineralTypes[0]->density.actualValue = 3205.83;
	_database->mineralTypes[0]->softness.actualValue = 1.0;
	_database->mineralTypes[0]->durability.actualValue = 7;
	_database->mineralTypes[0]->heatConductivity.actualValue = 12.0;

	_database->mineralTypes.push_back(std::make_shared<MineralType>());
	_database->mineralTypes[1]->density.actualValue = 2.56;
	_database->mineralTypes[1]->softness.actualValue = 2.0;
	_database->mineralTypes[1]->durability.actualValue = 6.5;
	_database->mineralTypes[1]->heatConductivity.actualValue = 1.90;

	_database->stoneTypes.push_back(std::make_shared<StoneType>());
	_database->stoneTypes[0]->minerals.resize(1);
	_database->stoneTypes[0]->minerals[0].type = _database->mineralTypes[0];
	_database->stoneTypes[0]->minerals[0].concentration.actualValue = 1.0;
	_database->stoneTypes[0]->density.actualValue = 3205.83;
	_database->stoneTypes[0]->softness.actualValue = 1.0;
	_database->stoneTypes[0]->durability.actualValue = 7;
	_database->stoneTypes[0]->heatConductivity.actualValue = 12.0;

	_database->stoneTypes.push_back(std::make_shared<StoneType>());
	_database->stoneTypes[1]->minerals.resize(2);
	_database->stoneTypes[1]->minerals[0].type = _database->mineralTypes[0];
	_database->stoneTypes[1]->minerals[0].concentration.actualValue = 0.5;
	_database->stoneTypes[1]->minerals[1].type = _database->mineralTypes[1];
	_database->stoneTypes[1]->minerals[1].concentration.actualValue = 0.5;
	_database->stoneTypes[1]->density.actualValue = 1604.19;
	_database->stoneTypes[1]->softness.actualValue = 1.5;
	_database->stoneTypes[1]->durability.actualValue = 6.75;
	_database->stoneTypes[1]->heatConductivity.actualValue = 6.95;

	_database->regions.resize(9);
	for (auto &region : _database->regions)
	{
		region.tiles.resize(16);
	}
	
	_database->regions[0].tiles[0].bedrock.mainStoneType = _database->stoneTypes[0];
	_database->regions[0].tiles[0].bedrock.deposits.resize(1);
	_database->regions[0].tiles[0].bedrock.deposits[0].stoneType = _database->stoneTypes[1];
	_database->regions[0].tiles[0].bedrock.deposits[0].bedrockDepth.actualValue = 100.0;
	_database->regions[0].tiles[0].bedrock.deposits[0].size.actualValue = 2500.0;
}

void GameLoadState::handleInput()
{
	sf::Event event;

	while (_engine->window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			_engine->window.close();
		}
	}
}

void GameLoadState::update(float delta)
{
	if (_clock.getElapsedTime().asSeconds() >= Define::SPLASH_STATE_DURATION)
	{
		_engine->machine.addState(stateRef(new WorldMap(_engine, _database)), true);
	}
}

void GameLoadState::draw()
{
	_engine->window.clear(sf::Color(sf::Color::White));

	_engine->window.display();
}