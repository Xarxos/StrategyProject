#pragma once

#include "Property.h"
#include <vector>

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