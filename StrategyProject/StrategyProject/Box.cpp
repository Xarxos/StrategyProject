#include "stdafx.h"
#include "Box.h"
#include "Defines.h"

#include <iostream>
#include <initializer_list>

Box::Box(EngineDataRef engineData, DatabaseRef database, int numOfTabs)
	: _engine(engineData),
	_database(database),
	_view(sf::Vector2f(Define::WORLD_VIEW_WIDTH / 2, Define::WORLD_VIEW_HEIGHT / 2), sf::Vector2f(Define::WORLD_VIEW_WIDTH, Define::WORLD_VIEW_HEIGHT)),
	_mouseButtonHeld(false),
	_openTabIndex(0)
{
	_tabs.reserve(numOfTabs);

	for (int i = 0; i < numOfTabs; i++)
	{
		_tabs.push_back(BoxTab(_engine, _database));
	}
}

Box::Box(EngineDataRef engineData, DatabaseRef database, const std::initializer_list<sf::String> &tabLabels)
	: _engine(engineData),
	_database(database),
	_view(sf::Vector2f(Define::WORLD_VIEW_WIDTH / 2, Define::WORLD_VIEW_HEIGHT / 2), sf::Vector2f(Define::WORLD_VIEW_WIDTH, Define::WORLD_VIEW_HEIGHT)),
	_mouseButtonHeld(false),
	_openTabIndex(0)
{
	_tabs.reserve(tabLabels.size());

	int loopCount(0);
	for (auto &tabLabel : tabLabels)
	{
		_tabs.push_back(BoxTab(_engine, _database));
		_tabs[loopCount].setTabLabel(tabLabel);
		loopCount++;
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

	for (int i = 0; i < _tabs.size(); i++)
	{
		_tabs[i].init();
		_tabs[i].setPosition(_background.getPosition().x + Graphics::BOX_TABS_EDGE_MARGIN + totalTabWidth, _background.getPosition().y + Graphics::BOX_TABS_EDGE_MARGIN);
		totalTabWidth += _tabs[i].getBounds().width;
	}

	_tabs[_openTabIndex].openTab(true);

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

		for (int i = 0; i < _tabs.size(); i++)
		{
			if (_tabs[i].getBounds().contains(sf::Mouse::getPosition(_engine->window).x, sf::Mouse::getPosition(_engine->window).y))
			{
				_tabs[_openTabIndex].openTab(false);
				_openTabIndex = i;
				_tabs[_openTabIndex].openTab(true);

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

		for (int i = 0; i < _tabs.size(); i++)
		{
			_tabs[i].setPosition(_tabs[i].getPosition().x + deltaMousePos.x, _tabs[i].getPosition().y + deltaMousePos.y);
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
		tab.drawTab();
	}

	_tabs[_openTabIndex].drawContents();

	_engine->window.draw(_closeButton);
}

void Box::setTabLabels(const std::initializer_list<sf::String> &tabLabels)
{
	if (tabLabels.size() > _tabs.size())
	{
		for (int i = _tabs.size(); i < tabLabels.size(); i++)
		{
			_tabs.push_back(BoxTab(_engine, _database));
		}
	}

	int loopCount(0);
	for (auto &tabLabel : tabLabels)
	{
		_tabs[loopCount].setTabLabel(tabLabel);
		loopCount++;
	}
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