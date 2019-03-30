#pragma once

#include "SFML\Graphics.hpp"
#include "Game.h"
#include "GameDatabase.h"
#include "Defines.h"
#include "SubState.h"

#include <vector>
#include <string>

struct SubStateLink
{
	sf::FloatRect boundingBox;
	subStateRef target;
};

template <T>
struct SubStateLin
{
	sf::FloatRect boundingBox;
	T targetData;
	subStateRef targetPointer;
};

class BoxTab
{
private:
	EngineDataRef _engine;
	DatabaseRef _database;

	sf::RectangleShape _tabShape;
	float _contentTopBounds;
	float _contentBottomBounds;
	sf::Text _tabLabel;

	std::vector<sf::Text> _texts;
	std::vector<sf::Sprite> _sprites;

	std::vector<SubStateLink> _subStateLinks;
	std::vector<SubStateLin> _subStateLins;

public:
	BoxTab(EngineDataRef engineData, DatabaseRef database);

	void init();

	void setTabPosition(float x, float y);

	void movePosition(float deltaX, float deltaY);
	void setTextRelativePosition(int textIndex, float x, float y);

	sf::Vector2f getPosition() const { return _tabShape.getPosition(); }
	sf::FloatRect getBounds() const { return _tabShape.getGlobalBounds(); }
	float getContentTopBounds() const { return _contentTopBounds; }
	float getContentBottomBounds() const { return _contentBottomBounds; }

	void setTabLabel(const sf::String &tabLabel);
	
	void addText(const sf::Text &text, const std::string &fontKey = "Box Tab Font", const sf::Color &textColor = Colors::BOX_TEXT, unsigned int textSize = Graphics::BOX_TEXT_SIZE);
	void addSprite(const sf::Sprite &sprite);
	void makeLink(sf::FloatRect boundingBox, subStateRef linkedSubState);
	
	template <typename T>
	void addLink(sf::FloatRect boundingBox, T linkedSubStateData, subStateRef linkedSubStatePointer);

	void openTab(bool open);

	bool handleInput();

	void drawTab();
	void drawContents();

private:
	void initTabLabel();
	void initTabShape();

	void updateContentTotalBounds();
};