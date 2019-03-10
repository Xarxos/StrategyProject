#pragma once

#include <vector>

#include "Bedrock.h"

struct Tile
{
	int ID;

	Bedrock bedrock;
};

struct Region
{
	std::vector<Tile> tiles;
};