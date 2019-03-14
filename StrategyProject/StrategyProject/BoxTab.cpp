#include "stdafx.h"
#include "SFML\Graphics.hpp"
#include "BoxTab.h"
#include "Defines.h"

BoxTab::BoxTab(EngineDataRef engineData, DatabaseRef database)
	: _engine(engineData),
	_database(database)
{

}

void BoxTab::init()
{
	initTabLabel();

	initTabShape();
}

void BoxTab::initTabLabel()
{
	_engine->assets.loadFont("Box Tab Font", Filepath::BOX_FONT);

	_tabLabel.setFont(_engine->assets.getFont("Box Tab Font"));
	_tabLabel.setFillColor(Colors::BOX_TEXT);
	_tabLabel.setCharacterSize(Graphics::BOX_TEXT_SIZE);
	_tabLabel.setOrigin(_tabLabel.getLocalBounds().left, _tabLabel.getLocalBounds().top);
}

void BoxTab::initTabShape()
{
	_tabShape.setOutlineThickness(Graphics::BOX_TAB_OUTLINE_THICKNESS);
	_tabShape.setOutlineColor(Colors::BOX_TAB_OUTLINE);
	_tabShape.setFillColor(Colors::BOX_TAB_CLOSED);
	_tabShape.setSize(sf::Vector2f(_tabLabel.getLocalBounds().width + _tabShape.getOutlineThickness() * 4, _tabLabel.getLocalBounds().height + _tabShape.getOutlineThickness() * 4));
}

void BoxTab::setPosition(float x, float y)
{
	_tabShape.setPosition(x, y);
	_tabLabel.setPosition(x + _tabShape.getOutlineThickness() * 2, y + _tabShape.getOutlineThickness() * 2);
}

void BoxTab::setTabLabel(const sf::String &tabLabel)
{
	_tabLabel.setString(tabLabel);
}

void BoxTab::openTab(bool open)
{ 
	if (open)
	{
		_tabShape.setFillColor(Colors::BOX_TAB_OPEN);
	}
	else
	{
		_tabShape.setFillColor(Colors::BOX_TAB_CLOSED);
	}
}

void BoxTab::drawTab()
{
	_engine->window.draw(_tabShape);
	_engine->window.draw(_tabLabel);
}

void BoxTab::drawContents()
{

}