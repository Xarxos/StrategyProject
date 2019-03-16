#include "stdafx.h"
#include "Box.h"
#include "Defines.h"

#include <iostream>
#include <initializer_list>

Box::Box(EngineDataRef engineData, DatabaseRef database, const std::initializer_list<sf::String> &tabLabels)
	: _engine(engineData),
	_database(database),
	_view(sf::Vector2f(Define::WORLD_VIEW_WIDTH / 2, Define::WORLD_VIEW_HEIGHT / 2), sf::Vector2f(Define::WORLD_VIEW_WIDTH, Define::WORLD_VIEW_HEIGHT)),
	_mouseButtonHeld(false),
	_openTabKey(""),
	_tabLabels(tabLabels)
{
	for (auto &tabLabel : tabLabels)
	{
		_tabs.insert(std::make_pair(tabLabel, BoxTab(_engine, _database)));
		_tabs.at(tabLabel).setTabLabel(tabLabel);
	}
}

void Box::init()
{
	_engine->assets.loadTexture("Box Background", Filepath::BOX_BACKGROUND);
	_engine->assets.loadTexture("Box Selected", Filepath::BOX_SELECTED);
	_engine->assets.loadTexture("Box Close Button", Filepath::BOX_CLOSE_BUTTON);

	_background.setTexture(&_engine->assets.getTexture("Box Background"));
	_closeButton.setTexture(_engine->assets.getTexture("Box Close Button"));

	float totalTabWidth(0.f);
	for (auto &tabLabel : _tabLabels)
	{
		_tabs.at(tabLabel).init();
		_tabs.at(tabLabel).setPosition(_background.getPosition().x + Graphics::BOX_TABS_EDGE_MARGIN + totalTabWidth, _background.getPosition().y + Graphics::BOX_TABS_EDGE_MARGIN);
		totalTabWidth += _tabs.at(tabLabel).getBounds().width;
	}

	_openTabKey = _tabLabels[0];
	_tabs.at(_openTabKey).openTab(true);

	_background.setSize(sf::Vector2f(totalTabWidth + Graphics::BOX_TABS_EDGE_MARGIN * 2, Graphics::BOX_DEFAULT_HEIGHT));

	_closeButton.setPosition(_background.getPosition().x + _background.getLocalBounds().width - _closeButton.getLocalBounds().width, _background.getPosition().y);
}

bool Box::handleInput(sf::Event &event)
{
	if (event.type == sf::Event::Closed)
	{
		_engine->window.close();
		return true;
	}

	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (handleMousePressEvent())
		{
			return true;
		}
	}

	if (event.type == sf::Event::MouseButtonReleased)
	{
		if (handleMouseReleaseEvent())
		{
			return true;
		}
	}

	return false;
}

bool Box::handleMousePressEvent()
{
	if (_engine->input.isSpriteClicked(_closeButton, sf::Mouse::Left, _engine->window))
	{
		_remove = true;
		return true;
	}

	if (_background.getGlobalBounds().contains(sf::Mouse::getPosition(_engine->window).x, sf::Mouse::getPosition(_engine->window).y))
	{
		_moveToTop = true;
		_mouseButtonHeld = true;
		_previousMousePos = _engine->input.getMousePosition(_engine->window);

		std::map<sf::String, BoxTab>::iterator it;

		for (it = _tabs.begin(); it != _tabs.end(); it++)
		{
			if (it->second.getBounds().contains(sf::Mouse::getPosition(_engine->window).x, sf::Mouse::getPosition(_engine->window).y))
			{
				_tabs.at(_openTabKey).openTab(false);
				_openTabKey = it->first;
				_tabs.at(_openTabKey).openTab(true);

				return true;
			}
		}

		return true;
	}

	return false;
}

bool Box::handleMouseReleaseEvent()
{
	if (_mouseButtonHeld)
	{
		_mouseButtonHeld = false;

		return true;
	}

	return false;
}

void Box::update(float delta)
{
	if (_mouseButtonHeld)
	{
		sf::Vector2i currentMousePos = _engine->input.getMousePosition(_engine->window);
		sf::Vector2i deltaMousePos = currentMousePos - _previousMousePos;

		_background.setPosition(_background.getPosition().x + deltaMousePos.x, _background.getPosition().y + deltaMousePos.y);
		_closeButton.setPosition(_closeButton.getPosition().x + deltaMousePos.x, _closeButton.getPosition().y + deltaMousePos.y);

		std::map<sf::String, BoxTab>::iterator it;

		for (it = _tabs.begin(); it != _tabs.end(); it++)
		{
			it->second.setPosition(it->second.getPosition().x + deltaMousePos.x, it->second.getPosition().y + deltaMousePos.y);
		}

		_previousMousePos = currentMousePos;
	}

	if (_moveToTop)
	{
		_moveToTop = false;
	}
}

void Box::draw()
{
	_engine->window.setView(_view);

	_engine->window.draw(_background);

	for (auto &tab : _tabs)
	{
		tab.second.drawTab();
	}

	_tabs.at(_openTabKey).drawContents();

	_engine->window.draw(_closeButton);
}

void Box::overwriteTabs(const std::initializer_list<sf::String> &tabLabels)
{
	_tabLabels = tabLabels;
	_tabs.clear();

	for (auto &tabLabel : _tabLabels)
	{
		_tabs.insert(std::make_pair(tabLabel, BoxTab(_engine, _database)));
		_tabs.at(tabLabel).setTabLabel(tabLabel);
	}

	float totalTabWidth(0.f);
	for (auto &tabLabel : _tabLabels)
	{
		_tabs.at(tabLabel).init();
		_tabs.at(tabLabel).setPosition(_background.getPosition().x + Graphics::BOX_TABS_EDGE_MARGIN + totalTabWidth, _background.getPosition().y + Graphics::BOX_TABS_EDGE_MARGIN);
		totalTabWidth += _tabs.at(tabLabel).getBounds().width;
	}

	_openTabKey = _tabLabels[0];
	_tabs.at(_openTabKey).openTab(true);

	_background.setSize(sf::Vector2f(totalTabWidth + Graphics::BOX_TABS_EDGE_MARGIN * 2, Graphics::BOX_DEFAULT_HEIGHT));

	_closeButton.setPosition(_background.getPosition().x + _background.getLocalBounds().width - _closeButton.getLocalBounds().width, _background.getPosition().y);
}

void Box::selectBox(bool isSelected)
{
	if (isSelected)
	{
		_background.setTexture(&_engine->assets.getTexture("Box Selected"));
	}
	else
	{
		_background.setTexture(&_engine->assets.getTexture("Box Background"));
	}
}