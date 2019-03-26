#pragma once

#include "Property.h"
#include <string>

struct MineralType
{
	sf::String name = "";

	Property<double> density;
	Property<double> softness;
	Property<double> durability;
	Property<double> heatConductivity;
};

typedef std::shared_ptr<MineralType> MineralTypeRef;

struct Mineral
{
	int typeIndex;
	Property<double> concentration;
};

