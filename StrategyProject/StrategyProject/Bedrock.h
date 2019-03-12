#pragma once

#include "Stone.h"
#include "Property.h"
#include <vector>

struct Deposit
{
	StoneTypeRef stoneType;
	Property<double> bedrockDepth;
	Property<double> size;
};

struct Bedrock
{
	StoneTypeRef mainStoneType;
	std::vector<Deposit> deposits;
};
