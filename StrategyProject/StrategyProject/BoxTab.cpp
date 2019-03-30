#include "stdafx.h"
#include "SFML\Graphics.hpp"
#include "BoxTab.h"
#include "Defines.h"
#include "MineralBox.h"
#include "SubState.h"

#include <string>
#include <iostream>
#include <type_traits>

BoxTab::BoxTab(EngineDataRef engineData, DatabaseRef database)
	: _engine(engineData),
	_database(database)
{

}

void BoxTab::init()
{
	initTabLabel();

	initTabShape();

	_contentTopBounds = 0.f;
	_contentBottomBounds = Graphics::BOX_DEFAULT_HEIGHT - Graphics::BOX_TABS_EDGE_MARGIN * 2 - _tabShape.getSize().y;
}

void BoxTab::initTabLabel()
{
	_engine->assets.loadFont("Box Tab Font", Filepath::BOX_FONT);

	_tabLabel.setFont(_engine->assets.getFont("Box Tab Font"));
	_tabLabel.setFillColor(Colors::BOX_TEXT);
	_tabLabel.setCharacterSize(Graphics::BOX_TAB_LABEL_TEXT_SIZE);
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
	_tabShape.move(deltaX, deltaY);
	_tabLabel.move(deltaX, deltaY);

}

void BoxTab::setTabLabel(const sf::String &tabLabel)
{
	_tabLabel.setString(tabLabel);
}

void BoxTab::addText(const sf::Text &text, const std::string &fontKey, const sf::Color &textColor, unsigned int textSize)
{
	_texts.push_back(text);
}

void BoxTab::makeLink(sf::FloatRect boundingBox, subStateRef linkedSubState)
{
	_subStateLinks.push_back(SubStateLink());
	_subStateLinks.back().boundingBox = boundingBox;
	_subStateLinks.back().target = std::move(linkedSubState);
}

template <typename T>
void BoxTab::addLink(sf::FloatRect boundingBox, T linkedSubStateData, subStateRef linkedSubStatePointer)
{

}

void BoxTab::setTextRelativePosition(int textIndex, float x, float y)
{
	_texts[textIndex].setPosition(x, y);

	updateContentTotalBounds();
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

bool BoxTab::handleInput()
{
	for (auto &link : _subStateLinks)
	{
		if (link.boundingBox.contains(sf::Mouse::getPosition(_engine->window).x, sf::Mouse::getPosition(_engine->window).y))
		{
			MineralBox boxy(_engine, _database, 0);
			//decltype(*link.target) mineralbox(_engine, _database, 0);
			subStateRef blob = std::move(subStateRef(new std::remove_pointer<decltype(dynamic_castlink.target.get())>::type(link.target)));
			_engine->machine.getActiveState()->getSubStates().push_back(std::move(link.target));
			_engine->machine.getActiveState()->getSubStates().back()->init();

			return true;
		}
	}

	return false;
}

void BoxTab::drawTab()
{
	_engine->window.draw(_tabShape);
	_engine->window.draw(_tabLabel);
}

void BoxTab::drawContents()
{
	for (auto &text : _texts)
	{
		_engine->window.draw(text);
	}
}

void BoxTab::updateContentTotalBounds()
{
	for (auto &text : _texts)
	{
		if (text.getGlobalBounds().top < _contentTopBounds)
		{
			_contentTopBounds = text.getGlobalBounds().top;
		}

		if (text.getGlobalBounds().top + text.getGlobalBounds().height > _contentBottomBounds)
		{
			_contentBottomBounds = text.getGlobalBounds().top + text.getGlobalBounds().height;
		}
	}

	for (auto &sprite : _sprites)
	{
		if (sprite.getGlobalBounds().top < _contentTopBounds)
		{
			_contentTopBounds = sprite.getGlobalBounds().top;
		}

		if (sprite.getGlobalBounds().top + sprite.getGlobalBounds().height > _contentBottomBounds)
		{
			_contentBottomBounds = sprite.getGlobalBounds().top + sprite.getGlobalBounds().height;
		}
	}
}