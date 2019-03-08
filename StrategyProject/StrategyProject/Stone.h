#pragma once

#include "Property.h"
#include <vector>
#include "Mineral.h"

class Stone
{
public:
	Stone();
	Stone(const std::vector<Mineral> &minerals);

	void init();
	void calculateProperties();

private:
	std::vector<Mineral> _minerals;

	Property<double> _density;
	Property<double> _softness;
	Property<double> _durability;
	Property<double> _heatConductivity;
};