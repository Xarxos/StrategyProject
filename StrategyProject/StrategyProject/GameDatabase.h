#pragma once

#include <vector>
#include <memory>

#include "Stone.h"
#include "Property.h"
#include "Bedrock.h"
#include "Tile.h"
#include "Mineral.h"

/*class Resource
{
private:
	int _ID;
	bool _isKnown;

	Property<double> _density;
	Property<double> _softness;
	Property<double> _durability;
	Property<double> _heatConductivity;
	Property<double> _flammability;
	Property<double> _burnHeat;
};

typedef std::unique_ptr<Resource> ResourceRef;

class BedrockResource
{
private:
	Resource _resource;

	Property<double> _avgDepth;
	Property<double> _concentration;
};





enum class ResourceType
{
	Material = 0
};*/





struct Database
{
	std::vector<Tile> tiles;
	std::vector<Region> regions;
	std::vector<Stone> stones;
	std::vector<MineralType> mineralTypes;
};

typedef std::shared_ptr<Database> DatabaseRef;