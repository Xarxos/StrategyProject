#include "stdafx.h"
#include "GameState.h"
#include "WorldMap.h"
#include "Defines.h"
#include "MainMenuState.h"
#include <iostream>

void GameState::init()
{
	_gameHUD.init();

	_game->machine.addState(stateRef(new WorldMap(_engine, _game)), false);
	_game->machine.processStateChanges();
}

void GameState::handleInput()
{
	_game->machine.processStateChanges();	// I'm not sure if having processStateChanges here could potentially cause problems.

	_game->machine.getActiveState()->handleInput();
}

void GameState::update(float delta)
{
	_game->machine.getActiveState()->update(delta);
}

void GameState::draw()
{
	_engine->window.clear(sf::Color(sf::Color::White));

	_game->machine.getActiveState()->draw();

	_gameHUD.draw();

	_engine->window.display();
}