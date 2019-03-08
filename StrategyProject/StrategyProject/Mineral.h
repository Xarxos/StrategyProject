#pragma once

#include "Property.h"

struct MineralType
{
	Property<double> density;
	Property<double> softness;
	Property<double> durability;
	Property<double> heatConductivity;
};

struct Mineral
{
	MineralType type;
	Property<double> concentration;
};
