#include "stdafx.h"
#include "Stone.h"
#include "Property.h"
#include <vector>
/*
StoneType::StoneType()
{

}

StoneType::StoneType(const std::vector<Mineral> &minerals)
	: _minerals(minerals)
{

}

void StoneType::init()
{
	calculateProperties();
}

void StoneType::calculateProperties()
{
	double totalMineralDensity(0.0);
	double totalMineralSoftness(0.0);
	double totalMineralDurability(0.0);
	double totalMineralHeatConductivity(0.0);

	for (auto &mineral : _minerals)
	{
		totalMineralDensity += mineral.type.density.actualValue * mineral.concentration.actualValue;
		totalMineralSoftness += mineral.type.softness.actualValue * mineral.concentration.actualValue;
		totalMineralDurability += mineral.type.durability.actualValue * mineral.concentration.actualValue;
		totalMineralHeatConductivity += mineral.type.heatConductivity.actualValue * mineral.concentration.actualValue;
	}

	_density.actualValue = totalMineralDensity / _minerals.size();
	_softness.actualValue = totalMineralSoftness / _minerals.size();
	_durability.actualValue = totalMineralDurability / _minerals.size();
	_heatConductivity.actualValue = totalMineralHeatConductivity / _minerals.size();
}
*/