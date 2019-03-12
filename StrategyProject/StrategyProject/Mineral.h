#pragma once

#include "Property.h"

struct MineralType
{
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

