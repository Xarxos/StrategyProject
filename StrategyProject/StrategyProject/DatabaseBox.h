#pragma once

#include "Box.h"
#include "GameDatabase.h"

class DatabaseBox : public Box
{
private:

public:
	DatabaseBox(EngineDataRef engineData, DatabaseRef database);

	virtual void init() override;

	virtual bool handleInput(sf::Event &event) override;
	virtual void update(float delta) override;
	virtual void draw() override;

private:
	
};