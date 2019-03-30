#include "stdafx.h"
#include "DatabaseBox.h"
#include "Defines.h"
#include "MineralBox.h"
#include "StoneBox.h"

#include <vector>
#include <iostream>

DatabaseBox::DatabaseBox(EngineDataRef engineData, DatabaseRef database)
	: Box(engineData, database, { "Minerals", "Stones" })
{

}

void DatabaseBox::init()
{
	Box::init();

	std::vector<int> mineralIndexes;

	for (int i = 0; i < _database->mineralTypes.size(); i++)
	{
		sf::String mineralString = _database->mineralTypes.at(i)->name;
		sf::Text mineral;
		mineral.setString(mineralString);
		mineral.setFont(_engine->assets.getFont("Box Tab Font"));
		mineral.setCharacterSize(Graphics::BOX_TEXT_SIZE);
		mineral.setFillColor(Colors::BOX_TEXT);

		_tabs.at("Minerals").addText(mineral);
		_tabs.at("Minerals").setTextRelativePosition(i, Graphics::BOX_TEXT_DEFAULT_X_OFFSET, Graphics::BOX_TEXT_SIZE * i);

		subStateRef mineralBox = std::make_shared<MineralBox>(_engine, _database, i);
		_tabs.at("Minerals").makeLink(_tabs.at("Minerals").getTextBounds(i), mineralBox);
	}

	for (int i = 0; i < _database->stoneTypes.size(); i++)
	{
		sf::String stoneString = _database->stoneTypes.at(i)->name;
		sf::Text stone;
		stone.setString(stoneString);
		stone.setFont(_engine->assets.getFont("Box Tab Font"));
		stone.setCharacterSize(Graphics::BOX_TEXT_SIZE);
		stone.setFillColor(Colors::BOX_TEXT);

		_tabs.at("Stones").addText(stone);
		_tabs.at("Stones").setTextRelativePosition(i, Graphics::BOX_TEXT_DEFAULT_X_OFFSET, Graphics::BOX_TEXT_SIZE * i);

		subStateRef stoneBox = std::make_shared<StoneBox>(_engine, _database, i);
		_tabs.at("Stones").makeLink(_tabs.at("Stones").getTextBounds(i), stoneBox);
	}
	
}

bool DatabaseBox::handleInput(sf::Event &event)
{
	if (Box::handleInput(event))
	{
		return true;
	}

	return false;
}
void DatabaseBox::update(float delta)
{
	if (_boxPressed)
	{
		sf::Vector2i currentMousePos = _engine->input.getMousePosition(_engine->window);
		sf::Vector2i deltaMousePos = currentMousePos - _previousMousePos;
	}

	Box::update(delta);
}
void DatabaseBox::draw()
{
	Box::draw();

	//_engine->window.draw(_enterButton);
}