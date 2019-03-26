#pragma once

#include "Stone.h"
#include "Property.h"
#include <vector>

struct Deposit
{
	int stoneTypeIndex;
	bool stoneTypeKnown;

	Property<double> bedrockDepth;
	Property<double> size;
};

struct Bedrock
{
	int mainStoneTypeIndex;
	bool mainStoneTypeKnown;

	std::vector<Deposit> deposits;
};
