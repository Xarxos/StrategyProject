#include "stdafx.h"
#include "MainMenuState.h"
#include "Defines.h"
#include "WorldMap.h"
#include <iostream>

void MainMenuState::init()
{
	_engine->assets.loadTexture("Main Menu Background", Filepath::MAIN_MENU_BACKGROUND);
	_engine->assets.loadTexture("Test Game Button", Filepath::TEST_GAME_BUTTON);
	_engine->assets.loadTexture("Exit Button", Filepath::EXIT_GAME_BUTTON);

	_background.setTexture(_engine->assets.getTexture("Main Menu Background"));
	_testGameButton.setTexture(_engine->assets.getTexture("Test Game Button"));
	_exitButton.setTexture(_engine->assets.getTexture("Exit Button"));

	_testGameButton.setOrigin(sf::Vector2f(_testGameButton.getLocalBounds().width / 2, _testGameButton.getLocalBounds().height / 2));
	_exitButton.setOrigin(sf::Vector2f(_exitButton.getLocalBounds().width / 2, _exitButton.getLocalBounds().height / 2));

	_testGameButton.setPosition(Define::SCREEN_WIDTH / 2, Define::SCREEN_HEIGHT / 3);
	_exitButton.setPosition(Define::SCREEN_WIDTH / 2, Define::SCREEN_HEIGHT / 3 * 2);
}

void MainMenuState::handleInput()
{
	sf::Event event;

	while (_engine->window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			_engine->window.close();
		}
		
		if (_engine->input.isSpriteClicked(_testGameButton, sf::Mouse::Left, _engine->window))
		{
			std::cout << "Attempt to add WorldMap...";
			_engine->machine.addState(stateRef(new WorldMap(_engine)), true);
			std::cout << "Success!\n";
		}
	}
}

void MainMenuState::update(float delta)
{

}

void MainMenuState::draw()
{
	_engine->window.clear(sf::Color(sf::Color::White));

	_engine->window.draw(_background);
	_engine->window.draw(_testGameButton);
	_engine->window.draw(_exitButton);

	_engine->window.display();
}