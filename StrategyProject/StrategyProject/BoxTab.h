#pragma once

#include "SFML\Graphics.hpp"
#include "Game.h"
#include "GameDatabase.h"

#include <vector>

class BoxTab
{
private:
	EngineDataRef _engine;
	DatabaseRef _database;

	sf::RectangleShape _tabShape;
	sf::Text _tabLabel;

	std::vector<sf::Text> _texts;
	std::vector<sf::Sprite> _sprites;

public:
	BoxTab(EngineDataRef engineData, DatabaseRef database);

	void init();

	void setPosition(float x, float y);

	sf::Vector2f getPosition() const { return _tabShape.getPosition(); }
	sf::FloatRect getBounds() const { return _tabShape.getGlobalBounds(); }

	void setTabLabel(const sf::String &tabLabel);

	void openTab(bool open);

	void drawTab();
	void drawContents();

private:
	void initTabLabel();
	void initTabShape();
};