#pragma once

#include "Box.h"
#include "GameDatabase.h"

#include <memory>

class StoneBox : public Box
{
private:
	StoneTypeRef _stoneType;

public:
	StoneBox(EngineDataRef engineData, DatabaseRef database, int stoneTypeIndex);

	virtual void init() override;

	virtual bool handleInput(sf::Event &event) override;
	virtual void update(float delta) override;
	virtual void draw() override;

private:

};
