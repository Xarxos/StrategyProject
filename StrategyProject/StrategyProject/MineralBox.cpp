#include "stdafx.h"
#include "MineralBox.h"
#include "Defines.h"

#include <vector>
#include <iostream>
#include <memory>

MineralBox::MineralBox(EngineDataRef engineData, DatabaseRef database, int mineralTypeIndex)
	: _mineralType(database->mineralTypes.at(mineralTypeIndex)),
	Box(engineData, database, { _mineralType->name })
{

}

void MineralBox::init()
{
	Box::init();

	sf::Text propertyText;
	propertyText.setFont(_engine->assets.getFont("Box Tab Font"));
	propertyText.setCharacterSize(Graphics::BOX_TEXT_SIZE);
	propertyText.setFillColor(Colors::BOX_TEXT);

	propertyText.setString("Density: ");
	_tabs.at(_mineralType->name).addText(propertyText);
	_tabs.at(_mineralType->name).setTextRelativePosition(0, Graphics::BOX_TEXT_DEFAULT_X_OFFSET, 0);

	propertyText.setString(std::to_string(_mineralType->density.actualValue));
	_tabs.at(_mineralType->name).addText(propertyText);
	_tabs.at(_mineralType->name).setTextRelativePosition(1, Graphics::BOX_TEXT_DEFAULT_X_OFFSET + propertyText.getLocalBounds().width, 0);

	propertyText.setString("Softness: ");
	_tabs.at(_mineralType->name).addText(propertyText);
	_tabs.at(_mineralType->name).setTextRelativePosition(2, Graphics::BOX_TEXT_DEFAULT_X_OFFSET, Graphics::BOX_TEXT_SIZE);

	propertyText.setString(std::to_string(_mineralType->softness.actualValue));
	_tabs.at(_mineralType->name).addText(propertyText);
	_tabs.at(_mineralType->name).setTextRelativePosition(3, Graphics::BOX_TEXT_DEFAULT_X_OFFSET + propertyText.getLocalBounds().width, Graphics::BOX_TEXT_SIZE);

	propertyText.setString("Durability: ");
	_tabs.at(_mineralType->name).addText(propertyText);
	_tabs.at(_mineralType->name).setTextRelativePosition(4, Graphics::BOX_TEXT_DEFAULT_X_OFFSET, Graphics::BOX_TEXT_SIZE * 2);

	propertyText.setString(std::to_string(_mineralType->durability.actualValue));
	_tabs.at(_mineralType->name).addText(propertyText);
	_tabs.at(_mineralType->name).setTextRelativePosition(5, Graphics::BOX_TEXT_DEFAULT_X_OFFSET + propertyText.getLocalBounds().width, Graphics::BOX_TEXT_SIZE * 2);

	propertyText.setString("Heat Conductivity: ");
	_tabs.at(_mineralType->name).addText(propertyText);
	_tabs.at(_mineralType->name).setTextRelativePosition(6, Graphics::BOX_TEXT_DEFAULT_X_OFFSET, Graphics::BOX_TEXT_SIZE * 3);

	propertyText.setString(std::to_string(_mineralType->heatConductivity.actualValue));
	_tabs.at(_mineralType->name).addText(propertyText);
	_tabs.at(_mineralType->name).setTextRelativePosition(7, Graphics::BOX_TEXT_DEFAULT_X_OFFSET + propertyText.getLocalBounds().width, Graphics::BOX_TEXT_SIZE * 3);
}

bool MineralBox::handleInput(sf::Event &event)
{
	if (Box::handleInput(event))
	{
		return true;
	}

	return false;
}
void MineralBox::update(float delta)
{
	Box::update(delta);
}
void MineralBox::draw()
{
	Box::draw();

	//_engine->window.draw(_enterButton);
}