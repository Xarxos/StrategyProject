#pragma once

#include <string>
#include "StateMachine.h"
#include "SFML\Graphics.hpp"

namespace Define
{
	const int SCREEN_WIDTH(800);
	const int SCREEN_HEIGHT(600);
	const std::string GAME_TITLE("Strategy Game");

	const float SPLASH_STATE_DURATION(0.5f);

	const int WORLD_SIZE(5);
	const int TILE_SIZE(100);
	const float TILE_TX_SIZE(180.f);
	const float WORLD_VIEW_WIDTH(SCREEN_WIDTH);
	const float WORLD_VIEW_HEIGHT(SCREEN_HEIGHT);
	const float WORLD_CAMERA_MOVE_SPEED(5.f);
	const float WORLD_CAMERA_ZOOM_FACTOR(10.f);
}

namespace Filepath
{
	const std::string SPLASH_STATE_BACKGROUND("Resources/Textures/SplashBackground.png");
	const std::string SPLASH_STATE_LOGO("Resources/Textures/SplashLogo.png");

	const std::string MAIN_MENU_BACKGROUND("Resources/Textures/MainMenuBackground.png");
	const std::string TEST_GAME_BUTTON("Resources/Textures/TestGameButton.png");
	const std::string EXIT_GAME_BUTTON("Resources/Textures/ExitButton.png");

	const std::string WORLD_MAP_BACKGROUND("Resources/Textures/WorldMapBackground.png");
	const std::string WORLD_MAP_BACKGROUND_GRAYSCALE("Resources/Textures/WorldMapBackgroundGrayScale.png");
}

namespace Colors
{
	const sf::Color MAP_MODE_DEFAULT(255, 255, 255);
	const sf::Color MAP_MODE_WATER(29, 52, 236);
	const sf::Color MAP_MODE_FLATGROUND(125, 181, 5);
}

namespace Controls
{
	const sf::Keyboard::Key CAMERA_MOVE_UP(sf::Keyboard::W);
	const sf::Keyboard::Key CAMERA_MOVE_DOWN(sf::Keyboard::S);
	const sf::Keyboard::Key CAMERA_MOVE_LEFT(sf::Keyboard::A);
	const sf::Keyboard::Key CAMERA_MOVE_RIGHT(sf::Keyboard::D);

	const sf::Keyboard::Key WORLD_MAP_MODE_DEFAULT(sf::Keyboard::Num0);
	const sf::Keyboard::Key WORLD_MAP_MODE_WATER(sf::Keyboard::Num1);
	const sf::Keyboard::Key WORLD_MAP_MODE_FLATGROUND(sf::Keyboard::Num2);
}