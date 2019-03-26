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

	printData();
}

void GameLoadState::loadMineralTypeData()
{
	for (int i = 0; i < WorldGenerator::NUM_OF_MINERAL_TYPES; i++)
	{
		_database->mineralTypes.push_back(std::make_shared<MineralType>());
		_database->mineralTypes[i]->name = generateName();

		_database->mineralTypes[i]->density.actualValue = GFunctions::getRandomDouble(WorldGenerator::MIN_MINERAL_DENSITY, WorldGenerator::MAX_MINERAL_DENSITY);
		_database->mineralTypes[i]->softness.actualValue = GFunctions::getRandomDouble(WorldGenerator::MIN_MINERAL_SOFTNESS, WorldGenerator::MAX_MINERAL_SOFTNESS);
		_database->mineralTypes[i]->durability.actualValue = GFunctions::getRandomDouble(WorldGenerator::MIN_MINERAL_DURABILITY, WorldGenerator::MAX_MINERAL_DURABILITY);
		_database->mineralTypes[i]->heatConductivity.actualValue = GFunctions::getRandomDouble(WorldGenerator::MIN_MINERAL_HEAT_CONDUCTIVITY, WorldGenerator::MAX_MINERAL_HEAT_CONDUCTIVITY);
	}
}

void GameLoadState::loadStoneTypeData()
{
	for (int i = 0; i < WorldGenerator::NUM_OF_STONE_TYPES; i++)
	{
		_database->stoneTypes.push_back(std::make_shared<StoneType>());
		_database->stoneTypes[i]->name = generateName();

		int numOfMinerals = GFunctions::getRandomInt(WorldGenerator::MIN_MINERALS_PER_STONE, WorldGenerator::MAX_MINERALS_PER_STONE);
		_database->stoneTypes[i]->minerals.resize(numOfMinerals);

		std::vector<double> mineralAmounts(numOfMinerals);
		double totalMineralAmount(0.0);

		for (int m = 0; m < numOfMinerals; m++)
		{
			mineralAmounts[m] = GFunctions::getRandomDouble(0.1, 100.0);
			totalMineralAmount += mineralAmounts[m];
		}

		for (int m = 0; m < numOfMinerals; m++)
		{
			_database->stoneTypes[i]->minerals[m].typeIndex = GFunctions::getRandomInt(0, _database->mineralTypes.size() - 1);

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
		totalMineralDensity += _database->mineralTypes[mineral.typeIndex]->density.actualValue * mineral.concentration.actualValue;
		totalMineralSoftness += _database->mineralTypes[mineral.typeIndex]->softness.actualValue * mineral.concentration.actualValue;
		totalMineralDurability += _database->mineralTypes[mineral.typeIndex]->durability.actualValue * mineral.concentration.actualValue;
		totalMineralHeatConductivity += _database->mineralTypes[mineral.typeIndex]->heatConductivity.actualValue * mineral.concentration.actualValue;
	}

	_database->stoneTypes[stoneTypeIndex]->density.actualValue = totalMineralDensity;
	_database->stoneTypes[stoneTypeIndex]->softness.actualValue = totalMineralSoftness;
	_database->stoneTypes[stoneTypeIndex]->durability.actualValue = totalMineralDurability;
	_database->stoneTypes[stoneTypeIndex]->heatConductivity.actualValue = totalMineralHeatConductivity;
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
		_database->regions[regionIndex].tiles[tileIndex].bedrock.mainStoneTypeIndex = GFunctions::getRandomInt(0, WorldGenerator::NUM_OF_STONE_TYPES - 1);

		int numOfDeposits = GFunctions::getRandomInt(WorldGenerator::MIN_DEPOSITS_PER_TILE, WorldGenerator::MAX_DEPOSITS_PER_TILE);
		_database->regions[regionIndex].tiles[tileIndex].bedrock.deposits.resize(numOfDeposits);

		for (auto &deposit : _database->regions[regionIndex].tiles[tileIndex].bedrock.deposits)
		{
			deposit.stoneTypeIndex = GFunctions::getRandomInt(0, WorldGenerator::NUM_OF_STONE_TYPES - 1);
			deposit.bedrockDepth.actualValue = GFunctions::getRandomDouble(WorldGenerator::MIN_DEPOSIT_DEPTH, WorldGenerator::MAX_DEPOSIT_DEPTH);
			deposit.size.actualValue = GFunctions::getRandomDouble(WorldGenerator::MIN_DEPOSIT_SIZE, WorldGenerator::MAX_DEPOSIT_SIZE);
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
		std::cout << i << ": " << std::string(_database->mineralTypes[i]->name) << "\n";
		std::cout << "\tDensity: " << _database->mineralTypes[i]->density.actualValue << "\n";
		std::cout << "\tSoftness: " << _database->mineralTypes[i]->softness.actualValue << "\n";
		std::cout << "\tDurability: " << _database->mineralTypes[i]->durability.actualValue << "\n";
		std::cout << "\tHeat Conductivity: " << _database->mineralTypes[i]->heatConductivity.actualValue << "\n";
	}

	std::cout << "\n";

	std::cout << "Stone Types\n-----------\n";
	for (int i = 0; i < WorldGenerator::NUM_OF_STONE_TYPES; i++)
	{
		std::cout << i << ": " << std::string(_database->stoneTypes[i]->name) << "\n";
		std::cout << "\tMinerals:\n";
		for (int m = 0; m < _database->stoneTypes[i]->minerals.size(); m++)
		{
			std::cout << "\t" << m << ":\n";
			std::cout << "\t\tType: " << std::string(_database->mineralTypes[_database->stoneTypes[i]->minerals[m].typeIndex]->name) << "\n";
			std::cout << "\t\tConcentration: " << _database->stoneTypes[i]->minerals[m].concentration.actualValue << "\n";
 		}

		std::cout << "\tDensity: " << _database->stoneTypes[i]->density.actualValue << "\n";
		std::cout << "\tSoftness: " << _database->stoneTypes[i]->softness.actualValue << "\n";
		std::cout << "\tDurability: " << _database->stoneTypes[i]->durability.actualValue << "\n";
		std::cout << "\tHeat Conductivity: " << _database->stoneTypes[i]->heatConductivity.actualValue << "\n";
	}

	std::cout << "\n";

	std::cout << "Bedrocks\n--------\n";
	for (int regionIndex = 0; regionIndex < WorldGenerator::NUM_OF_REGIONS; regionIndex++)
	{
		for (int tileIndex = 0; tileIndex < WorldGenerator::TILES_PER_REGION; tileIndex++)
		{
			std::cout << "Region " << regionIndex << ", Tile " << tileIndex << ":\n";
			std::cout << "\tMain Stone Type: " << std::string(_database->stoneTypes[_database->regions[regionIndex].tiles[tileIndex].bedrock.mainStoneTypeIndex]->name)  << "\n";

			std::cout << "\tDeposits:\n";
			int loopCount(0);
			for (auto &deposit : _database->regions[regionIndex].tiles[tileIndex].bedrock.deposits)
			{
				std::cout << "\t" << loopCount++ << ":\n";
				std::cout << "\t\tStone Type: " << std::string(_database->stoneTypes[deposit.stoneTypeIndex]->name) << "\n";
				std::cout << "\t\tBedrock Depth: " << deposit.bedrockDepth.actualValue << "\n";
				std::cout << "\t\tSize: " << deposit.size.actualValue << "\n";
			}
		}
	}
}

std::string GameLoadState::generateName()
{
	std::vector<std::string> startBits =
	{
		"Ar", "Pu", "Ol", "Me", "Ne", "Ti", "Al", "We", "Ru", "So", "Ke", "Qua", "Xe", "Li"
	};

	std::vector<std::string> middleBits =
	{
		"mi", "wa", "xa", "lo", "om", "un", "es", "by", "op", "ze", "ez", "que", "cu", "el"
	};

	std::vector<std::string> endBits =
	{
		"tite", "nite", "ite"
	};

	std::string name(startBits.at(GFunctions::getRandomInt(0, startBits.size() - 1)));
	name.append(middleBits.at(GFunctions::getRandomInt(0, middleBits.size() - 1)));
	name.append(endBits.at(GFunctions::getRandomInt(0, endBits.size() - 1)));

	return name;
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