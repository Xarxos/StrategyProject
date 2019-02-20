#include "stdafx.h"
#include "SplashState.h"
#include "Defines.h"
#include "MainMenuState.h"

void SplashState::init()
{
	_engine->assets.loadTexture("Splash Background", Filepath::SPLASH_STATE_BACKGROUND);
	_engine->assets.loadTexture("Splash Logo", Filepath::SPLASH_STATE_LOGO);

	_background.setTexture(_engine->assets.getTexture("Splash Background"));
	_logo.setTexture(_engine->assets.getTexture("Splash Logo"));

	_logo.setOrigin(sf::Vector2f(_logo.getLocalBounds().width / 2, _logo.getLocalBounds().height / 2));
	_logo.setPosition(Define::SCREEN_WIDTH / 2, Define::SCREEN_HEIGHT / 2);
}

void SplashState::handleInput()
{
	sf::Event event;

	while (_engine->window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			_engine->window.close();
		}
	}
}

void SplashState::update(float delta)
{
	if (_clock.getElapsedTime().asSeconds() >= Define::SPLASH_STATE_DURATION)
	{
		_engine->machine.addState(stateRef(new MainMenuState(_engine)), true);
	}
}

void SplashState::draw()
{
	_engine->window.clear(sf::Color(sf::Color::White));

	_engine->window.draw(_background);
	_engine->window.draw(_logo);

	_engine->window.display();
}