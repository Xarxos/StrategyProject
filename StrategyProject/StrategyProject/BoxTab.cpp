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
	initTabLabel();

	initTabShape();

	_contentTopBounds = 0.f;
	_contentBottomBounds = Graphics::BOX_DEFAULT_HEIGHT - Graphics::BOX_TABS_EDGE_MARGIN * 2 - _tabShape.getLocalBounds().height;
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