#include "stdafx.h"
#include "GameLoadState.h"
#include "Defines.h"
#include "WorldMap.h"
#include "Stone.h"
#include "GeneralFunctions.h"

#include <memory>
#include <vector>
#include <iostream>

void GameLoadState::init()
{
	loadMineralTypeData();
	loadStoneTypeData();
	loadRegionData();
}

void GameLoadState::loadMineralTypeData()
{
	for (int i = 0; i < WorldGenerator::NUM_OF_MINERAL_TYPES; i++)
	{
		_database->mineralTypes.push_back(std::make_shared<MineralType>());
		_database->mineralTypes[i]->density.actualValue = getRandomDouble(WorldGenerator::MIN_MINERAL_DENSITY, WorldGenerator::MAX_MINERAL_DENSITY);
		_database->mineralTypes[i]->softness.actualValue = getRandomDouble(WorldGenerator::MIN_MINERAL_SOFTNESS, WorldGenerator::MAX_MINERAL_SOFTNESS);
		_database->mineralTypes[i]->durability.actualValue = getRandomDouble(WorldGenerator::MIN_MINERAL_DURABILITY, WorldGenerator::MAX_MINERAL_DURABILITY);
		_database->mineralTypes[i]->heatConductivity.actualValue = getRandomDouble(WorldGenerator::MIN_MINERAL_HEAT_CONDUCTIVITY, WorldGenerator::MAX_MINERAL_HEAT_CONDUCTIVITY);
	}
}

void GameLoadState::loadStoneTypeData()
{
	for (int i = 0; i < WorldGenerator::NUM_OF_STONE_TYPES; i++)
	{
		_database->stoneTypes.push_back(std::make_shared<StoneType>());

		int numOfMinerals = getRandomInt(WorldGenerator::MIN_MINERALS_PER_STONE, WorldGenerator::MAX_MINERALS_PER_STONE);
		_database->stoneTypes[i]->minerals.resize(numOfMinerals);

		std::vector<double> mineralAmounts(numOfMinerals);
		double totalMineralAmount(0.0);

		for (int m = 0; m < numOfMinerals; m++)
		{
			mineralAmounts[m] = getRandomDouble(0.1, 100.0);
			totalMineralAmount += mineralAmounts[m];
		}

		for (int m = 0; m < numOfMinerals; m++)
		{
			_database->stoneTypes[i]->minerals[m].type = _database->mineralTypes[getRandomInt(0, _database->mineralTypes.size() - 1)];

			double currentMineralConcentration = mineralAmounts[m] / totalMineralAmount;
			_database->stoneTypes[i]->minerals[m].concentration.actualValue = currentMineralConcentration;
		}
		
		calculateStoneProperties(i);
	}
}

void GameLoadState::calculateStoneProperties(int stoneTypeIndex)
{
	double totalMineralDensity(0.0);
	double totalMineralSoftness(0.0);
	double totalMineralDurability(0.0);
	double totalMineralHeatConductivity(0.0);

	for (auto &mineral : _database->stoneTypes[stoneTypeIndex]->minerals)
	{
		totalMineralDensity += mineral.type->density.actualValue * mineral.concentration.actualValue;
		totalMineralSoftness += mineral.type->softness.actualValue * mineral.concentration.actualValue;
		totalMineralDurability += mineral.type->durability.actualValue * mineral.concentration.actualValue;
		totalMineralHeatConductivity += mineral.type->heatConductivity.actualValue * mineral.concentration.actualValue;
	}

	_database->stoneTypes[stoneTypeIndex]->density.actualValue = totalMineralDensity / _database->stoneTypes[stoneTypeIndex]->minerals.size();
	_database->stoneTypes[stoneTypeIndex]->softness.actualValue = totalMineralSoftness / _database->stoneTypes[stoneTypeIndex]->minerals.size();
	_database->stoneTypes[stoneTypeIndex]->durability.actualValue = totalMineralDurability / _database->stoneTypes[stoneTypeIndex]->minerals.size();
	_database->stoneTypes[stoneTypeIndex]->heatConductivity.actualValue = totalMineralHeatConductivity / _database->stoneTypes[stoneTypeIndex]->minerals.size();
}

void GameLoadState::loadRegionData()
{
	_database->regions.resize(WorldGenerator::NUM_OF_REGIONS);

	for (int regionIndex = 0; regionIndex < WorldGenerator::NUM_OF_REGIONS; regionIndex++)
	{
		_database->regions[regionIndex].tiles.resize(WorldGenerator::TILES_PER_REGION);
		loadTileData(regionIndex);
	}
}

void GameLoadState::loadTileData(int regionIndex)
{
	for (int tileIndex = 0; tileIndex < WorldGenerator::TILES_PER_REGION; tileIndex++)
	{
		_database->regions[regionIndex].tiles[tileIndex].bedrock.mainStoneType = _database->stoneTypes[getRandomInt(0, WorldGenerator::NUM_OF_STONE_TYPES)];

		int numOfDeposits = getRandomInt(WorldGenerator::MIN_DEPOSITS_PER_TILE, WorldGenerator::MAX_DEPOSITS_PER_TILE);
		_database->regions[regionIndex].tiles[tileIndex].bedrock.deposits.resize(numOfDeposits);

		for (auto &deposit : _database->regions[regionIndex].tiles[tileIndex].bedrock.deposits)
		{
			deposit.stoneType = _database->stoneTypes[getRandomInt(0, WorldGenerator::NUM_OF_STONE_TYPES)];
			deposit.bedrockDepth.actualValue = getRandomDouble(WorldGenerator::MIN_DEPOSIT_DEPTH, WorldGenerator::MAX_DEPOSIT_DEPTH);
			deposit.size.actualValue = getRandomDouble(WorldGenerator::MIN_DEPOSIT_SIZE, WorldGenerator::MAX_DEPOSIT_SIZE);
		}
	}
}

void GameLoadState::calculateRegionData(int regionIndex)
{
	
}

void GameLoadState::printData()
{
	std::cout << "Mineral Types\n-------------\n";
	for (int i = 0; i < WorldGenerator::NUM_OF_MINERAL_TYPES; i++)
	{
		std::cout << i << ":\n";
		std::cout << "\tDensity: " << _database->mineralTypes[i]->density.actualValue << "\n";
		std::cout << "\tSoftness: " << _database->mineralTypes[i]->softness.actualValue << "\n";
		std::cout << "\tDurability: " << _database->mineralTypes[i]->durability.actualValue << "\n";
		std::cout << "\tHeat Conductivity: " << _database->mineralTypes[i]->heatConductivity.actualValue << "\n";
	}

	std::cout << "Stone Types\n-----------\n";
	for (int i = 0; i < WorldGenerator::NUM_OF_STONE_TYPES; i++)
	{
		std::cout << i << ":\n";
		std::cout << "\tMinerals:\n";
		for (int m = 0; m < _database->stoneTypes[i]->minerals.size(); m++)
		{
			std::cout << m << ":\n";
			_database->stoneTypes[i]->mi
		}
		std::cout << _database->stoneTypes[i]->minerals
		std::cout << "\tDensity: " << _database->stoneTypes[i]->density.actualValue << "\n";
		std::cout << "\tSoftness: " << _database->stoneTypes[i]->softness.actualValue << "\n";
		std::cout << "\tDurability: " << _database->stoneTypes[i]->durability.actualValue << "\n";
		std::cout << "\tHeat Conductivity: " << _database->stoneTypes[i]->heatConductivity.actualValue << "\n";
	}
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