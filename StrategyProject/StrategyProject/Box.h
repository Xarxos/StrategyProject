#pragma once

#include "SFML\Graphics.hpp"
#include "BoxTab.h"
#include "SubState.h"
#include "Game.h"
#include "GameDatabase.h"

#include <vector>

class Box : public SubState
{
private:
	EngineDataRef _engine;
	DatabaseRef _database;

	sf::View _view;

	sf::RectangleShape _background;
	sf::Texture _texture;
	sf::Sprite _closeButton;

	std::vector<BoxTab> _tabs;
	int _openTabIndex;

	bool _mouseButtonHeld;
	sf::Vector2i _previousMousePos;

public:
	Box(EngineDataRef engineData, DatabaseRef database);

	virtual void init() override;

	virtual bool handleInput(sf::Event &event) override;
	virtual void update(float delta) override;
	virtual void draw() override;

	void selectBox(bool isSelected = true);
};