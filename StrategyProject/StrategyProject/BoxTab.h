#pragma once

#include "SFML\Graphics.hpp"
#include "Game.h"
#include "GameDatabase.h"
#include "Defines.h"

#include <vector>
#include <string>

class BoxTab
{
private:
	EngineDataRef _engine;
	DatabaseRef _database;

	sf::RectangleShape _tabShape;
	sf::RectangleShape _contentArea;
	sf::Text _tabLabel;
	sf::RectangleShape _scrollBar;
	sf::RectangleShape _scrollHandle;

	std::vector<sf::Text> _texts;
	std::vector<sf::Sprite> _sprites;

public:
	BoxTab(EngineDataRef engineData, DatabaseRef database);

	void init();

	void setTabPosition(float x, float y);

	void movePosition(float deltaX, float deltaY);
	void setContentAreaSize(const sf::Vector2f &size) { _contentArea.setSize(size); }
	void setContentAreaPosition(float x, float y) { _contentArea.setPosition(x, y); }
	void setTextPosition(int textIndex, float x, float y) { _texts[textIndex].setPosition(x, y); }

	sf::Vector2f getPosition() const { return _tabShape.getPosition(); }
	sf::FloatRect getBounds() const { return _tabShape.getGlobalBounds(); }

	void setTabLabel(const sf::String &tabLabel);
	
	void addText(const sf::Text &text, const std::string &fontKey = "Box Tab Font", const sf::Color &textColor = Colors::BOX_TEXT, unsigned int textSize = Graphics::BOX_TEXT_SIZE);
	
	void addSprite(const sf::Sprite &sprite);

	void openTab(bool open);

	void drawTab();
	void drawContents();

private:
	void initTabLabel();
	void initTabShape();
};