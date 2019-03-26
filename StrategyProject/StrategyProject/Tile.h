#pragma once

#include <vector>

#include "Bedrock.h"
#include "Property.h"

struct Tile
{
	int ID;

	Bedrock bedrock;
};

struct Region
{
	std::vector<Tile> tiles;
};