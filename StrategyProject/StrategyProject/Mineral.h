#pragma once

#include "Property.h"
#include <string>

struct MineralType
{
	std::string name = "";

	Property<double> density;
	Property<double> softness;
	Property<double> durability;
	Property<double> heatConductivity;
};

typedef std::shared_ptr<MineralType> MineralTypeRef;

struct Mineral
{
	MineralTypeRef type;
	Property<double> concentration;
};

