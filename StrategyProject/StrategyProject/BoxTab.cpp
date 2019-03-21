#include "stdafx.h"
#include "SFML\Graphics.hpp"
#include "BoxTab.h"
#include "Defines.h"

#include <string>

BoxTab::BoxTab(EngineDataRef engineData, DatabaseRef database)
	: _engine(engineData),
	_database(database)
{

}

void BoxTab::init()
{
	_contentArea.setOutlineThickness(Graphics::BOX_TAB_OUTLINE_THICKNESS);
	_contentArea.setOutlineColor(sf::Color::Black);

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

void BoxTab::setTabPosition(float x, float y)
{
	_tabShape.setPosition(x, y);
	_tabLabel.setPosition(x + _tabShape.getOutlineThickness() * 2, y + _tabShape.getOutlineThickness() * 2);
}

void BoxTab::movePosition(float deltaX, float deltaY)
{
	_tabShape.setPosition(_tabShape.getPosition().x + deltaX, _tabShape.getPosition().y + deltaY);
	_tabLabel.setPosition(_tabLabel.getPosition().x + deltaX, _tabLabel.getPosition().y + deltaY);
	_contentArea.setPosition(_contentArea.getPosition().x + deltaX, _contentArea.getPosition().y + deltaY);

	for (int i = 0; i < _texts.size(); i++)
	{
		_texts[i].setPosition(_texts[i].getPosition().x + deltaX, _texts[i].getPosition().y + deltaY);
	}
}

void BoxTab::setTabLabel(const sf::String &tabLabel)
{
	_tabLabel.setString(tabLabel);
}

void BoxTab::addText(const sf::Text &text, const std::string &fontKey, const sf::Color &textColor, unsigned int textSize)
{
	_texts.push_back(text);
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
	_engine->window.draw(_contentArea);
}

void BoxTab::drawContents()
{
	for (auto &text : _texts)
	{
		_engine->window.draw(text);
	}
}