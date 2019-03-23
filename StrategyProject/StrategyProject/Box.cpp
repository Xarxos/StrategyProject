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
	
}

void Box::init()
{
	_engine->assets.loadTexture("Box Background", Filepath::BOX_BACKGROUND);
	_engine->assets.loadTexture("Box Selected", Filepath::BOX_SELECTED);
	_engine->assets.loadTexture("Box Close Button", Filepath::BOX_CLOSE_BUTTON);

	_background.setTexture(&_engine->assets.getTexture("Box Background"));
	_closeButton.setTexture(_engine->assets.getTexture("Box Close Button"));

	setupTabs();
}

void Box::setupTabs()
{
	for (auto &tabLabel : _tabLabels)
	{
		_tabs.insert(std::make_pair(tabLabel, BoxTab(_engine, _database)));
		_tabs.at(tabLabel).setTabLabel(tabLabel);
		_tabs.at(tabLabel).init();
	}

	updateGraphics();
}

void Box::updateGraphics()
{
	float tabHeight(0.f);
	float totalTabWidth(0.f);
	for (auto &tabLabel : _tabLabels)
	{
		_tabs.at(tabLabel).setTabPosition(_background.getPosition().x + Graphics::BOX_TABS_EDGE_MARGIN + totalTabWidth, _background.getPosition().y + Graphics::BOX_TABS_EDGE_MARGIN);
		totalTabWidth += _tabs.at(tabLabel).getBounds().width;
		tabHeight = _tabs.at(tabLabel).getBounds().height;
	}

	_openTabKey = _tabLabels[0];
	_tabs.at(_openTabKey).openTab(true);

	_background.setSize(sf::Vector2f(totalTabWidth + _closeButton.getLocalBounds().width + Graphics::BOX_TABS_EDGE_MARGIN * 2, Graphics::BOX_DEFAULT_HEIGHT));

	_contentArea.width = _background.getLocalBounds().width - Graphics::BOX_TABS_EDGE_MARGIN * 2;
	_contentArea.height = _background.getLocalBounds().height - Graphics::BOX_TABS_EDGE_MARGIN * 2 - tabHeight;
	_contentArea.left = _background.getPosition().x + Graphics::BOX_TABS_EDGE_MARGIN;
	_contentArea.top = _background.getPosition().y + Graphics::BOX_TABS_EDGE_MARGIN + tabHeight;

	_scrollBar.setSize(sf::Vector2f(Graphics::BOX_SCROLL_BAR_WIDTH, _contentArea.height));
	_scrollBar.setPosition(_contentArea.left + _contentArea.width - Graphics::BOX_SCROLL_BAR_WIDTH, _contentArea.top);
	_scrollBar.setOutlineThickness(Graphics::BOX_SCROLL_BAR_OUTLINE_THICKNESS);
	_scrollBar.setOutlineColor(sf::Color::Black);
	_scrollBar.setFillColor(Colors::BOX_SCROLL_BAR);

	_scrollHandle.setSize(sf::Vector2f(Graphics::BOX_SCROLL_BAR_WIDTH * 1.5, Graphics::BOX_SCROLL_BAR_WIDTH / 2));
	_scrollHandle.setPosition(_scrollBar.getPosition().x - Graphics::BOX_SCROLL_BAR_WIDTH * 0.25, _scrollBar.getPosition().y);
	_scrollHandle.setOutlineThickness(Graphics::BOX_SCROLL_BAR_OUTLINE_THICKNESS);
	_scrollHandle.setOutlineColor(sf::Color::Black);
	_scrollHandle.setFillColor(Colors::BOX_SCROLL_HANDLE);

	_tabContentView.setCenter(_contentArea.width / 2, _contentArea.height / 2);
	_tabContentView.setSize(_contentArea.width, _contentArea.height);
	_tabContentView.setViewport(sf::FloatRect(_contentArea.left / Define::SCREEN_WIDTH, _contentArea.top / Define::SCREEN_HEIGHT, _contentArea.width / Define::SCREEN_WIDTH, _contentArea.height / Define::SCREEN_HEIGHT));

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

		_contentArea.left += deltaMousePos.x;
		_contentArea.top += deltaMousePos.y;

		_scrollBar.setPosition(_scrollBar.getPosition().x + deltaMousePos.x, _scrollBar.getPosition().y + deltaMousePos.y);
		_scrollHandle.setPosition(_scrollHandle.getPosition().x + deltaMousePos.x, _scrollHandle.getPosition().y + deltaMousePos.y);

		_tabContentView.setViewport(sf::FloatRect(_contentArea.left / Define::SCREEN_WIDTH, _contentArea.top / Define::SCREEN_HEIGHT, _contentArea.width / Define::SCREEN_WIDTH, _contentArea.height / Define::SCREEN_HEIGHT));

		std::map<sf::String, BoxTab>::iterator it;

		for (it = _tabs.begin(); it != _tabs.end(); it++)
		{
			it->second.movePosition(deltaMousePos.x, deltaMousePos.y);
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

	_engine->window.setView(_tabContentView);
	_tabs.at(_openTabKey).drawContents();

	_engine->window.setView(_view);

	_engine->window.draw(_scrollBar);
	_engine->window.draw(_scrollHandle);
	_engine->window.draw(_closeButton);
}

void Box::overwriteTabs(const std::initializer_list<sf::String> &tabLabels)
{
	_tabLabels = tabLabels;
	_tabs.clear();

	setupTabs();
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