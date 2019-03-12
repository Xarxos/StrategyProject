#pragma once

#include <vector>
#include <memory>

#include "Property.h"
#include "Mineral.h"

struct StoneType
{
	std::vector<Mineral> minerals;

	Property<double> density;
	Property<double> softness;
	Property<double> durability;
	Property<double> heatConductivity;
};

typedef std::shared_ptr<StoneType> StoneTypeRef;