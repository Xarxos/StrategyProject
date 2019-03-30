#pragma once

#include "Box.h"
#include "GameDatabase.h"

#include <memory>

class MineralBox : public Box
{
private:
	MineralTypeRef _mineralType;

public:
	MineralBox(EngineDataRef engineData, DatabaseRef database, int mineralTypeIndex);

	virtual void init() override;

	virtual bool handleInput(sf::Event &event) override;
	virtual void update(float delta) override;
	virtual void draw() override;

private:

};
