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

class Bedrock
{
private:
	Stone _mainStoneType;
	std::vector<Deposit> _deposits;
};
