#pragma once

#include "SFML\Graphics.hpp"
#include "BoxTab.h"
#include "SubState.h"
#include "Game.h"
#include "GameDatabase.h"

#include <vector>
#include <map>
#include <string>
#include <initializer_list>

class Box : public SubState
{
protected:
	EngineDataRef _engine;
	DatabaseRef _database;

	sf::View _view;
	sf::View _tabContentView;

	sf::RectangleShape _background;
	sf::Texture _texture;
	sf::FloatRect _contentArea;
	sf::RectangleShape _scrollBar;
	sf::RectangleShape _scrollHandle;
	sf::Sprite _closeButton;

	std::map<sf::String, BoxTab> _tabs;
	std::vector<sf::String> _tabLabels;
	sf::String _openTabKey;

	bool _mouseButtonHeld;
	sf::Vector2i _previousMousePos;

public:
	Box(EngineDataRef engineData, DatabaseRef database, const std::initializer_list<sf::String> &tabLabels);

	virtual void init() override;

	virtual bool handleInput(sf::Event &event) override;
	virtual void update(float delta) override;
	virtual void draw() override;

	void overwriteTabs(const std::initializer_list<sf::String> &tabLabels);

	void selectBox(bool isSelected = true);

private:
	void setupTabs();
	void updateGraphics();
	bool handleMousePressEvent();
	bool handleMouseReleaseEvent();
};