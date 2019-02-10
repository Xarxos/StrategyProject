#include "stdafx.h"
#include "MainMenuState.h"
#include "Defines.h"
#include "WorldMap.h"
#include <iostream>

void MainMenuState::init()
{
	_data->assets.loadTexture("Main Menu Background", Filepath::MAIN_MENU_BACKGROUND);
	_data->assets.loadTexture("Test Game Button", Filepath::TEST_GAME_BUTTON);
	_data->assets.loadTexture("Exit Button", Filepath::EXIT_GAME_BUTTON);

	_background.setTexture(_data->assets.getTexture("Main Menu Background"));
	_testGameButton.setTexture(_data->assets.getTexture("Test Game Button"));
	_exitButton.setTexture(_data->assets.getTexture("Exit Button"));

	_testGameButton.setOrigin(sf::Vector2f(_testGameButton.getLocalBounds().width / 2, _testGameButton.getLocalBounds().height / 2));
	_exitButton.setOrigin(sf::Vector2f(_exitButton.getLocalBounds().width / 2, _exitButton.getLocalBounds().height / 2));

	_testGameButton.setPosition(Define::SCREEN_WIDTH / 2, Define::SCREEN_HEIGHT / 3);
	_exitButton.setPosition(Define::SCREEN_WIDTH / 2, Define::SCREEN_HEIGHT / 3 * 2);
}

void MainMenuState::handleInput()
{
	sf::Event event;

	while (_data->window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			_data->window.close();
		}
		
		if (_data->input.isSpriteClicked(_testGameButton, sf::Mouse::Left, _data->window))
		{
			std::cout << "Attempt to add WorldMap...";
			_data->machine.addState(stateRef(new WorldMap(_data)), true);
			std::cout << "Success!\n";
		}
	}
}

void MainMenuState::update(float delta)
{

}

void MainMenuState::draw()
{
	_data->window.clear(sf::Color(sf::Color::White));

	_data->window.draw(_background);
	_data->window.draw(_testGameButton);
	_data->window.draw(_exitButton);

	_data->window.display();
}