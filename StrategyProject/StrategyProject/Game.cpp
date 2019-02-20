#include "stdafx.h"
#include "Game.h"
#include <SFML\Graphics.hpp>
#include "Config.h"
#include "SplashState.h"

Game::Game(int windowWidth, int windowHeight, std::string title)
{
	_engine->window.create(sf::VideoMode(windowWidth, windowHeight), title, sf::Style::Close | sf::Style::Titlebar);
	_engine->machine.addState(stateRef(new SplashState(_engine)));

	run();
}

void Game::run()
{
	float newTime, frameTime;

	float currentTime = _clock.getElapsedTime().asSeconds();

	float accumulator = 0.0f;

	while (_engine->window.isOpen())
	{
		_engine->machine.processStateChanges();

		newTime = _clock.getElapsedTime().asSeconds();

		frameTime = newTime - currentTime;

		currentTime = newTime;
		accumulator += frameTime;

		while (accumulator >= Config::FRAME_RATE)
		{
			_engine->machine.getActiveState()->handleInput();
			_engine->machine.getActiveState()->update(Config::FRAME_RATE);

			accumulator -= Config::FRAME_RATE;
		}
		_engine->machine.getActiveState()->draw();
	}
}