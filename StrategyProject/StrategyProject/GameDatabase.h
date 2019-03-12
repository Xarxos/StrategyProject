#pragma once

#include <vector>
#include <memory>

#include "Stone.h"
#include "Property.h"
#include "Bedrock.h"
#include "Tile.h"
#include "Mineral.h"

struct Database
{
	std::vector<Region> regions;
	std::vector<StoneTypeRef> stoneTypes;
	std::vector<MineralTypeRef> mineralTypes;
};

typedef std::shared_ptr<Database> DatabaseRef;