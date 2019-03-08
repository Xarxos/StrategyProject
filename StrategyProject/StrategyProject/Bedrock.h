#pragma once

#include "Stone.h"
#include "Property.h"
#include <vector>

struct Deposit
{
	Stone stoneType;
	Property<double> bedrockDepth;
	Property<double> size;
};

struct Bedrock
{
	Stone mainStoneType;
	std::vector<Deposit> deposits;
};
