#include "stdafx.h"
#include "StoneBox.h"
#include "Defines.h"

#include <vector>
#include <iostream>
#include <memory>

StoneBox::StoneBox(EngineDataRef engineData, DatabaseRef database, int stoneTypeIndex)
	: _stoneType(database->stoneTypes.at(stoneTypeIndex)),
	Box(engineData, database, { "" })
{
	overwriteTabs({ _stoneType->name });
}

void StoneBox::init()
{
	Box::init();

	sf::Text propertyText;
	propertyText.setFont(_engine->assets.getFont("Box Tab Font"));
	propertyText.setCharacterSize(Graphics::BOX_TEXT_SIZE);
	propertyText.setFillColor(Colors::BOX_TEXT);

	propertyText.setString("Density: ");
	_tabs.at(_stoneType->name).addText(propertyText);
	_tabs.at(_stoneType->name).setTextRelativePosition(0, Graphics::BOX_TEXT_DEFAULT_X_OFFSET, 0);

	propertyText.setString(std::to_string(_stoneType->density.actualValue));
	_tabs.at(_stoneType->name).addText(propertyText);
	_tabs.at(_stoneType->name).setTextRelativePosition(1, Graphics::BOX_TEXT_DEFAULT_X_OFFSET + propertyText.getLocalBounds().width, 0);

	propertyText.setString("Softness: ");
	_tabs.at(_stoneType->name).addText(propertyText);
	_tabs.at(_stoneType->name).setTextRelativePosition(2, Graphics::BOX_TEXT_DEFAULT_X_OFFSET, Graphics::BOX_TEXT_SIZE);

	propertyText.setString(std::to_string(_stoneType->softness.actualValue));
	_tabs.at(_stoneType->name).addText(propertyText);
	_tabs.at(_stoneType->name).setTextRelativePosition(3, Graphics::BOX_TEXT_DEFAULT_X_OFFSET + propertyText.getLocalBounds().width, Graphics::BOX_TEXT_SIZE);

	propertyText.setString("Durability: ");
	_tabs.at(_stoneType->name).addText(propertyText);
	_tabs.at(_stoneType->name).setTextRelativePosition(4, Graphics::BOX_TEXT_DEFAULT_X_OFFSET, Graphics::BOX_TEXT_SIZE * 2);

	propertyText.setString(std::to_string(_stoneType->durability.actualValue));
	_tabs.at(_stoneType->name).addText(propertyText);
	_tabs.at(_stoneType->name).setTextRelativePosition(5, Graphics::BOX_TEXT_DEFAULT_X_OFFSET + propertyText.getLocalBounds().width, Graphics::BOX_TEXT_SIZE * 2);

	propertyText.setString("Heat Conductivity: ");
	_tabs.at(_stoneType->name).addText(propertyText);
	_tabs.at(_stoneType->name).setTextRelativePosition(6, Graphics::BOX_TEXT_DEFAULT_X_OFFSET, Graphics::BOX_TEXT_SIZE * 3);

	propertyText.setString(std::to_string(_stoneType->heatConductivity.actualValue));
	_tabs.at(_stoneType->name).addText(propertyText);
	_tabs.at(_stoneType->name).setTextRelativePosition(7, Graphics::BOX_TEXT_DEFAULT_X_OFFSET + propertyText.getLocalBounds().width, Graphics::BOX_TEXT_SIZE * 3);
}

bool StoneBox::handleInput(sf::Event &event)
{
	if (Box::handleInput(event))
	{
		return true;
	}

	return false;
}
void StoneBox::update(float delta)
{
	Box::update(delta);
}
void StoneBox::draw()
{
	Box::draw();

	//_engine->window.draw(_enterButton);
}