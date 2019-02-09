#include "stdafx.h"
#include <SFML\Graphics.hpp>
#include "InputManager.h"
#include <iostream>

bool InputManager::isSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow &window)
{
	if (sf::Mouse::isButtonPressed(button))
	{
		if (object.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
		{
			return true;
		}
	}

	return false;
}

sf::Vector2i InputManager::getMousePosition(sf::RenderWindow &window)
{
	return sf::Mouse::getPosition(window);
}