#include "stdafx.h"
#include "SplashState.h"
#include "Defines.h"

void SplashState::init()
{
	_data->assets.loadTexture("Splash Background", Filepath::SPLASH_STATE_BACKGROUND);
	_data->assets.loadTexture("Splash Logo", Filepath::SPLASH_STATE_LOGO);

	_background.setTexture(_data->assets.getTexture("Splash Background"));
	_logo.setTexture(_data->assets.getTexture("Splash Logo"));

	_logo.setOrigin(sf::Vector2f(_logo.getLocalBounds().width / 2, _logo.getLocalBounds().height / 2));
	_logo.setPosition(Define::SCREEN_WIDTH / 2, Define::SCREEN_HEIGHT / 2);
}

void SplashState::handleInput()
{

}

void SplashState::update(float delta)
{
	//TODO: Implement state change, to LoadState probably.
}

void SplashState::draw()
{
	_data->window.clear(sf::Color(sf::Color::White));

	_data->window.draw(_background);
	_data->window.draw(_logo);

	_data->window.display();
}