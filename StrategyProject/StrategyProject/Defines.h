#pragma once

#include <string>
#include "StateMachine.h"
#include "SFML\Graphics.hpp"

namespace Define
{
	const int SCREEN_WIDTH(1600);
	const int SCREEN_HEIGHT(1000);
	const std::string GAME_TITLE("Strategy Game");

	const float SPLASH_STATE_DURATION(0.5f);

	const int WORLD_SIZE_IN_TILES_X(110);	// These need to have the same ratio between X and Y as WORLD_TX_SIZE has between its X and Y.
	const int WORLD_SIZE_IN_TILES_Y(40);
	const int DEFAULT_MAP_SIZE(500);
	const int TILE_SIZE(50);	// Beware of integer division, could maybe cause a problem I dunno?

	const int WORLD_TX_SIZE_X(5500);	// The size and ratio of these values need to allow for whole numbers for both WORLD_SIZE_IN_TILES and TILE_TX_SIZE.
	const int WORLD_TX_SIZE_Y(2000);
	const int TILE_TX_SIZE(50);	// Beware of integer division, could maybe cause a problem I dunno?

	const float WORLD_VIEW_WIDTH(SCREEN_WIDTH);
	const float WORLD_VIEW_HEIGHT(SCREEN_HEIGHT);
	const float WORLD_CAMERA_MOVE_SPEED(5.f);
	const float WORLD_CAMERA_ZOOM_FACTOR(1.1f);
	const int WORLD_CAMERA_EDGE_MARGIN(100);
	const float WORLD_CAMERA_MAX_ZOOM_FACTOR(2.f);
	const float WORLD_CAMERA_MIN_ZOOM_FACTOR(0.5f);

	const float MINIMAP_SIZE_FACTOR(0.20f);

	const sf::Color DATA_COLOR_WATER(sf::Color(29, 52, 226));
	const sf::Color DATA_COLOR_FLATGROUND(sf::Color(125, 181, 5));
	const sf::Color DATA_COLOR_HILLS(sf::Color(153, 136, 108));
	const sf::Color DATA_COLOR_MOUNTAINS(sf::Color(255, 255, 255));
	const sf::Color DATA_COLOR_FOREST(sf::Color(13, 153, 32));

	const float TILE_SELECT_OUTLINE_THICKNESS(TILE_SIZE / 10);
}

namespace Filepath
{
	const std::string SPLASH_STATE_BACKGROUND("Resources/Textures/SplashBackground.png");
	const std::string SPLASH_STATE_LOGO("Resources/Textures/SplashLogo.png");

	const std::string MAIN_MENU_BACKGROUND("Resources/Textures/MainMenuBackground.png");
	const std::string TEST_GAME_BUTTON("Resources/Textures/TestGameButton.png");
	const std::string EXIT_GAME_BUTTON("Resources/Textures/ExitButton.png");

	//const std::string WORLD_MAP_BACKGROUND("Resources/Textures/WorldMapBackground.png");
	//const std::string WORLD_MAP_BACKGROUND_GRAYSCALE("Resources/Textures/WorldMapBackgroundGrayScale.png");
	//const std::string WORLD_MAP_BACKGROUND("Resources/Data/terrain.bmp");
	//const std::string WORLD_MAP_BACKGROUND_GRAYSCALE("Resources/Data/terrainGrayscale.bmp");
	const std::string WORLD_MAP_BACKGROUND("Resources/Data/bigmap.bmp");
	const std::string WORLD_MAP_BACKGROUND_GRAYSCALE("Resources/Data/bigmapGrayscale.bmp");

	const std::string HUD_BACKGROUND("Resources/Textures/HUDBackground.png");

	const std::string TILE_DATA_BOX_BACKGROUND("Resources/Textures/TileDataBoxBackground.png");
	const std::string TILE_DATA_BOX_SELECTED("Resources/Textures/TileDataBoxSelected.png");
	const std::string TILE_DATA_BOX_FONT("Resources/Fonts/ARBONNIE.ttf");
	const std::string TILE_DATA_BOX_CLOSE_BUTTON("Resources/Textures/DataBoxCloseButton.png");
}

namespace Colors
{
	const sf::Color MAP_MODE_DEFAULT(255, 255, 255);
	const sf::Color MAP_MODE_WATER(0, 0, 255);
	const sf::Color MAP_MODE_FLATGROUND(255, 255, 0);
	const sf::Color MAP_MODE_HILLS(0, 255, 255);
	const sf::Color MAP_MODE_MOUNTAINS(255, 0, 0);
	const sf::Color MAP_MODE_FOREST(0, 255, 0);

	const sf::Color TILE_SELECT_HIGHLIGHT_COLOR(sf::Color::Magenta);
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
	const sf::Keyboard::Key WORLD_MAP_MODE_HILLS(sf::Keyboard::Num3);
	const sf::Keyboard::Key WORLD_MAP_MODE_MOUNTAINS(sf::Keyboard::Num4);
	const sf::Keyboard::Key WORLD_MAP_MODE_FOREST(sf::Keyboard::Num5);
}