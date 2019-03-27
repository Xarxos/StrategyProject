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

	const int WORLD_SIZE_IN_TILES_X(3);	// These need to have the same ratio between X and Y as WORLD_TX_SIZE has between its X and Y.
	const int WORLD_SIZE_IN_TILES_Y(3);
	const int DEFAULT_MAP_SIZE(500);
	const int TILE_SIZE(1000);

	const int WORLD_TX_SIZE_X(3000);	// The size and ratio of these values need to allow for whole numbers for both WORLD_SIZE_IN_TILES and TILE_TX_SIZE.
	const int WORLD_TX_SIZE_Y(3000);
	const int TILE_TX_SIZE(1000);

	const int REGION_SIZE_IN_TILES_X(4);	// These need to have the same ratio between X and Y as REGION_TX_SIZE has between its X and Y.
	const int REGION_SIZE_IN_TILES_Y(4);
	const int REGION_TILE_SIZE(750);

	const int REGION_TX_SIZE_X(1000);	// The size and ratio of these values need to allow for whole numbers for both REGION_SIZE_IN_TILES and REGION_TILE_TX_SIZE.
	const int REGION_TX_SIZE_Y(1000);
	const int REGION_TILE_TX_SIZE(250);

	const float WORLD_VIEW_WIDTH(SCREEN_WIDTH);
	const float WORLD_VIEW_HEIGHT(SCREEN_HEIGHT);
	const float WORLD_CAMERA_MOVE_SPEED(5.f);
	const float WORLD_CAMERA_ZOOM_FACTOR(1.1f);
	const int WORLD_CAMERA_EDGE_MARGIN(100);
	const float WORLD_CAMERA_MAX_ZOOM_FACTOR(2.f);
	const float WORLD_CAMERA_MIN_ZOOM_FACTOR(0.5f);

	const float REGION_VIEW_WIDTH(SCREEN_WIDTH);
	const float REGION_VIEW_HEIGHT(SCREEN_HEIGHT);
	const float REGION_CAMERA_MOVE_SPEED(5.f);
	const float REGION_CAMERA_ZOOM_FACTOR(1.1f);
	const int REGION_CAMERA_EDGE_MARGIN(100);
	const float REGION_CAMERA_MAX_ZOOM_FACTOR(2.f);
	const float REGION_CAMERA_MIN_ZOOM_FACTOR(0.5f);

	const float MINIMAP_SIZE_FACTOR(0.20f);

	const sf::Color DATA_COLOR_WATER(sf::Color(29, 52, 226));
	const sf::Color DATA_COLOR_FLATGROUND(sf::Color(125, 181, 5));
	const sf::Color DATA_COLOR_HILLS(sf::Color(153, 136, 108));
	const sf::Color DATA_COLOR_MOUNTAINS(sf::Color(255, 255, 255));
	const sf::Color DATA_COLOR_FOREST(sf::Color(13, 153, 32));

	const float TILE_SELECT_OUTLINE_THICKNESS(TILE_SIZE / 25);
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
	//const std::string WORLD_MAP_BACKGROUND("Resources/Data/bigmap.bmp");
	//const std::string WORLD_MAP_BACKGROUND_GRAYSCALE("Resources/Data/bigmapGrayscale.bmp");
	const std::string WORLD_MAP_BACKGROUND("Resources/Textures/Maps/Scandinavia.png");
	const std::string WORLD_MAP_BACKGROUND_GRAYSCALE("Resources/Textures/Maps/Scandinavia.png");

	//const std::string REGION1_MAP_BACKGROUND("Resources/Data/RegionBotten.png");
	//const std::string REGION1_MAP_BACKGROUND_GRAYSCALE("Resources/Data/RegionBottenGrayscale.png");
	const std::string REGION1_MAP_BACKGROUND("Resources/Textures/Maps/31.png");
	const std::string REGION1_MAP_BACKGROUND_GRAYSCALE("Resources/Textures/Maps/31.png");

	const std::string HUD_TOP_SHELF("Resources/Textures/HUDTopShelf.png");
	const std::string DATABASE_BUTTON("Resources/Textures/DatabaseButton.png");

	const std::string BOX_BACKGROUND("Resources/Textures/TileDataBoxBackground.png");
	const std::string BOX_SELECTED("Resources/Textures/TileDataBoxSelected.png");
	const std::string BOX_FONT("Resources/Fonts/arial.ttf");
	const std::string BOX_CLOSE_BUTTON("Resources/Textures/DataBoxCloseButton.png");
	const std::string TILE_DATA_BOX_ENTER_BUTTON("Resources/Textures/DataBoxEnterButton.png");
}

namespace Graphics
{
	const unsigned int BOX_HEADLINE_TEXT_SIZE(20);
	const unsigned int BOX_TEXT_SIZE(15);
	const unsigned int BOX_TAB_LABEL_TEXT_SIZE(30);
	const sf::Text::Style BOX_HEADLINE_TEXT_STYLE(sf::Text::Bold);
	const float BOX_TEXT_DEFAULT_X_OFFSET(10.f);

	const float BOX_TAB_OUTLINE_THICKNESS(2.f);
	const float BOX_TABS_EDGE_MARGIN(10.f);

	const float BOX_DEFAULT_HEIGHT(200.f);
	const float BOX_MIN_WIDTH(500.f);
	const float BOX_SCROLL_BAR_WIDTH(20.f);
	const float BOX_SCROLL_BAR_OUTLINE_THICKNESS(2.f);

	const sf::Vector2f HUD_DATABASE_BUTTON_POSITION(30.f, 30.f);
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

	const sf::Color BOX_TAB_OPEN(255, 255, 255, 175);
	const sf::Color BOX_TAB_CLOSED(255, 255, 255, 0);
	const sf::Color BOX_TAB_OUTLINE(sf::Color::Black);
	const sf::Color BOX_TEXT(sf::Color::Black);
	const sf::Color BOX_SCROLL_BAR(125, 125, 125);
	const sf::Color BOX_SCROLL_HANDLE(95, 95, 95);
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

namespace WorldGenerator
{
	const int TILES_PER_REGION(16);
	const int NUM_OF_REGIONS(9);
	const int NUM_OF_MINERAL_TYPES(10);
	const int NUM_OF_STONE_TYPES(10);

	const int MIN_MINERALS_PER_STONE(2);
	const int MAX_MINERALS_PER_STONE(5);
	const int MIN_DEPOSITS_PER_TILE(0);
	const int MAX_DEPOSITS_PER_TILE(5);

	const double MAX_MINERAL_DENSITY(1000.0);
	const double MIN_MINERAL_DENSITY(10.0);
	const double MAX_MINERAL_SOFTNESS(1000.0);
	const double MIN_MINERAL_SOFTNESS(10.0);
	const double MAX_MINERAL_DURABILITY(1000.0);
	const double MIN_MINERAL_DURABILITY(10.0);
	const double MAX_MINERAL_HEAT_CONDUCTIVITY(1000.0);
	const double MIN_MINERAL_HEAT_CONDUCTIVITY(10.0);

	const double MAX_DEPOSIT_DEPTH(100.0);
	const double MIN_DEPOSIT_DEPTH(0.0);
	const double MAX_DEPOSIT_SIZE(1000.0);
	const double MIN_DEPOSIT_SIZE(10.0);
}