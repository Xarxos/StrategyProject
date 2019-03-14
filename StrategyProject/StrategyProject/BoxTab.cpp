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
	_engine->assets.loadFont("Box Tab Font", Filepath::BOX_FONT);

	_tabText.setFont(_engine->assets.getFont("Box Tab Font"));
	_tabText.setFillColor(Colors::BOX_TEXT);
	_tabText.setCharacterSize(Graphics::BOX_TEXT_SIZE);
	_tabText.setString("Tab Text");
	_tabText.setOrigin(_tabText.getLocalBounds().left, _tabText.getLocalBounds().top);

	_tabShape.setOutlineThickness(Graphics::BOX_TAB_OUTLINE_THICKNESS);
	_tabShape.setOutlineColor(Colors::BOX_TAB_OUTLINE);
	_tabShape.setFillColor(Colors::BOX_TAB_CLOSED);
	_tabShape.setSize(sf::Vector2f(_tabText.getLocalBounds().width + _tabShape.getOutlineThickness() * 4, _tabText.getLocalBounds().height + _tabShape.getOutlineThickness() * 4));
}

void BoxTab::setPosition(float x, float y)
{
	_tabShape.setPosition(x, y);
	_tabText.setPosition(x + _tabShape.getOutlineThickness() * 2, y + _tabShape.getOutlineThickness() * 2);
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
	_engine->window.draw(_tabText);
}

void BoxTab::drawContents()
{

}