#pragma once

#include "Stone.h"
#include "Property.h"
#include <vector>

struct Deposit
{
	StoneTypeRef stoneType;
	bool stoneTypeKnown;

	Property<double> bedrockDepth;
	Property<double> size;
};

struct Bedrock
{
	StoneTypeRef mainStoneType;
	bool mainStoneTypeKnown;

	std::vector<Deposit> deposits;
};
