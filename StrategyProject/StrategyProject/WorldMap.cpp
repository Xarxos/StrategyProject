#include "stdafx.h"
#include "WorldMap.h"
#include "Defines.h"
#include <vector>
#include "SFML\Graphics.hpp"
#include <iostream>

WorldMap::WorldMap(GameDataRef data)
	: _data(data),
	_tileMatrix(Define::WORLD_SIZE, std::vector<int>(Define::WORLD_SIZE)),
	_vertices(sf::Quads, Define::WORLD_SIZE * Define::WORLD_SIZE * 4),
	_view(sf::Vector2f(Define::WORLD_VIEW_WIDTH / 2, Define::WORLD_VIEW_HEIGHT / 2), sf::Vector2f(Define::WORLD_VIEW_WIDTH, Define::WORLD_VIEW_HEIGHT))
{
	_tileTerrains[Terrain::Water].resize(Define::WORLD_SIZE * Define::WORLD_SIZE);
	_tileTerrains[Terrain::FlatGround].resize(Define::WORLD_SIZE * Define::WORLD_SIZE);
	_tileTerrains[Terrain::Hills].resize(Define::WORLD_SIZE * Define::WORLD_SIZE);
	_tileTerrains[Terrain::Mountains].resize(Define::WORLD_SIZE * Define::WORLD_SIZE);
	_tileTerrains[Terrain::Forest].resize(Define::WORLD_SIZE * Define::WORLD_SIZE);
	
	/*_tileTerrains[Terrain::Water] =
	{
		0.05, 0.01, 0.08, 0.95, 0.01,
		0.02, 0.02, 0.03, 0.60, 0.40,
		0.65, 0.20, 0.10, 0.90, 0.65,
		0.35, 0.35, 0.25, 0.95, 0.10,
		0.15, 0.55, 0.85, 0.55, 0.07
	};

	_tileTerrains[Terrain::FlatGround] =
	{
		0.20, 0.30, 0.85, 0.05, 0.99,
		0.40, 0.92, 0.97, 0.40, 0.60,
		0.30, 0.80, 0.90, 0.10, 0.35,
		0.65, 0.65, 0.75, 0.05, 0.90,
		0.85, 0.45, 0.15, 0.45, 0.93
	};*/
}

void WorldMap::init()
{
	std::cout << "Start init().\n";
	sf::Clock clock;
	float start = clock.getElapsedTime().asSeconds();

	_data->assets.loadImage("World Map Terrain Data", Filepath::WORLD_MAP_BACKGROUND);
	_data->assets.loadTexture("World Map Background", Filepath::WORLD_MAP_BACKGROUND);
	_data->assets.loadTexture("World Map Background Grayscale", Filepath::WORLD_MAP_BACKGROUND_GRAYSCALE);
	_backgroundTexture = _data->assets.getTexture("World Map Background");
	_terrainData = _data->assets.getImage("World Map Terrain Data");

	for (int row = 0; row < Define::WORLD_SIZE; row++)
	{
		for (int column = 0; column < Define::WORLD_SIZE; column++)
		{
			_tileMatrix[row][column] = row * Define::WORLD_SIZE + column;
			int quadIndex = _tileMatrix[row][column] * 4;

			_vertices[quadIndex + 0].position = sf::Vector2f(column * Define::TILE_SIZE, row * Define::TILE_SIZE);
			_vertices[quadIndex + 1].position = sf::Vector2f(column * Define::TILE_SIZE + Define::TILE_SIZE, row * Define::TILE_SIZE);
			_vertices[quadIndex + 2].position = sf::Vector2f(column * Define::TILE_SIZE + Define::TILE_SIZE, row * Define::TILE_SIZE + Define::TILE_SIZE);
			_vertices[quadIndex + 3].position = sf::Vector2f(column * Define::TILE_SIZE, row * Define::TILE_SIZE + Define::TILE_SIZE);

			_vertices[quadIndex + 0].color = sf::Color(sf::Color::Green);
			_vertices[quadIndex + 1].color = sf::Color(sf::Color::Red);
			_vertices[quadIndex + 2].color = sf::Color(sf::Color::Blue);
			_vertices[quadIndex + 3].color = sf::Color(sf::Color::Magenta);

			_vertices[quadIndex + 0].texCoords = sf::Vector2f(column * Define::TILE_TX_SIZE, row * Define::TILE_TX_SIZE);
			_vertices[quadIndex + 1].texCoords = sf::Vector2f(column * Define::TILE_TX_SIZE + Define::TILE_TX_SIZE, row * Define::TILE_TX_SIZE);
			_vertices[quadIndex + 2].texCoords = sf::Vector2f(column * Define::TILE_TX_SIZE + Define::TILE_TX_SIZE, row * Define::TILE_TX_SIZE + Define::TILE_TX_SIZE);
			_vertices[quadIndex + 3].texCoords = sf::Vector2f(column * Define::TILE_TX_SIZE, row * Define::TILE_TX_SIZE + Define::TILE_TX_SIZE);
		}
	}

	loadTerrainData();

	float end = clock.getElapsedTime().asSeconds();
	std::cout << "Loaded " << Define::WORLD_SIZE * Define::WORLD_SIZE << " tiles in " << end - start << " seconds.\n";
}

void WorldMap::handleInput()
{
	sf::Event event;

	while (_data->window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			_data->window.close();
		}

		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				sf::Vector2i worldMouse(_data->window.mapPixelToCoords(sf::Mouse::getPosition(_data->window), _view).x, _data->window.mapPixelToCoords(sf::Mouse::getPosition(_data->window), _view).y);
				std::cout << "World Mouse: " << worldMouse.x << "," << worldMouse.y << "\n";

				int tileClicked(coordsToTile(worldMouse));
				std::cout << "Tile Clicked: " << tileClicked << "\n";
				std::cout << "Water: " << _tileTerrains.at(Terrain::Water)[tileClicked] << "\n";
				std::cout << "Flat Ground: " << _tileTerrains.at(Terrain::FlatGround)[tileClicked] << "\n";
				std::cout << "Hills: " << _tileTerrains.at(Terrain::Hills)[tileClicked] << "\n";
				std::cout << "Mountains: " << _tileTerrains.at(Terrain::Mountains)[tileClicked] << "\n";
				std::cout << "Forest: " << _tileTerrains.at(Terrain::Forest)[tileClicked] << "\n";
			}
		}

		if (event.type == sf::Event::MouseWheelScrolled)
		{
			if (event.mouseWheelScroll.delta >= 0)
			{
				_view.zoom(Define::WORLD_CAMERA_ZOOM_FACTOR);
			}
			else
			{
				_view.zoom(1 / Define::WORLD_CAMERA_ZOOM_FACTOR);
			}
		}

		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == Controls::WORLD_MAP_MODE_DEFAULT)
			{
				changeMapMode(Terrain::Default);
			}
			if (event.key.code == Controls::WORLD_MAP_MODE_WATER)
			{
				changeMapMode(Terrain::Water);
			}
			if (event.key.code == Controls::WORLD_MAP_MODE_FLATGROUND)
			{
				changeMapMode(Terrain::FlatGround);
			}
			if (event.key.code == Controls::WORLD_MAP_MODE_HILLS)
			{
				changeMapMode(Terrain::Hills);
			}
			if (event.key.code == Controls::WORLD_MAP_MODE_MOUNTAINS)
			{
				changeMapMode(Terrain::Mountains);
			}
			if (event.key.code == Controls::WORLD_MAP_MODE_FOREST)
			{
				changeMapMode(Terrain::Forest);
			}
		}
	}

	if (sf::Keyboard::isKeyPressed(Controls::CAMERA_MOVE_UP))
	{
		if (_view.getCenter().y - _view.getSize().y / 2 > 0)
		{
			_view.move(0.f, -Define::WORLD_CAMERA_MOVE_SPEED);
		}
	}
	if (sf::Keyboard::isKeyPressed(Controls::CAMERA_MOVE_DOWN))
	{
		if (_view.getCenter().y + _view.getSize().y / 2 < Define::WORLD_SIZE * Define::TILE_SIZE)
		{
			_view.move(0.f, Define::WORLD_CAMERA_MOVE_SPEED);
		}
	}
	if (sf::Keyboard::isKeyPressed(Controls::CAMERA_MOVE_LEFT))
	{
		if (_view.getCenter().x - _view.getSize().x / 2 > 0)
		{
			_view.move(-Define::WORLD_CAMERA_MOVE_SPEED, 0.f);
		}
	}
	if (sf::Keyboard::isKeyPressed(Controls::CAMERA_MOVE_RIGHT))
	{
		if (_view.getCenter().x + _view.getSize().x / 2 < Define::WORLD_SIZE * Define::TILE_SIZE)
		{
			_view.move(Define::WORLD_CAMERA_MOVE_SPEED, 0.f);
		}
	}
}

void WorldMap::update(float delta)
{

}

void WorldMap::draw()
{
	_data->window.clear(sf::Color(sf::Color::White));

	_data->window.setView(_view);

	_data->window.draw(_vertices, &_backgroundTexture);

	_data->window.display();
}

void WorldMap::loadTerrainData()
{
	std::cout << "Load Terrain Data...\n";
	for (int row = 0; row < Define::WORLD_SIZE; row++)
	{
		for (int column = 0; column < Define::WORLD_SIZE; column++)
		{
			int waterPixels(0);
			int flatgroundPixels(0);
			int hillPixels(0);
			int mountainPixels(0);
			int forestPixels(0);

			for (int pixelRow = 0; pixelRow < Define::TILE_TX_SIZE; pixelRow++)
			{
				for (int pixelColumn = 0; pixelColumn < Define::TILE_TX_SIZE; pixelColumn++)
				{
					if (_terrainData.getPixel(column * Define::TILE_TX_SIZE + pixelColumn, row * Define::TILE_TX_SIZE + pixelRow) == Define::DATA_COLOR_WATER)
					{
						waterPixels++;
					}
					else if (_terrainData.getPixel(column * Define::TILE_TX_SIZE + pixelColumn, row * Define::TILE_TX_SIZE + pixelRow) == Define::DATA_COLOR_FLATGROUND)
					{
						flatgroundPixels++;
					}
					else if (_terrainData.getPixel(column * Define::TILE_TX_SIZE + pixelColumn, row * Define::TILE_TX_SIZE + pixelRow) == Define::DATA_COLOR_HILLS)
					{
						hillPixels++;
					}
					else if (_terrainData.getPixel(column * Define::TILE_TX_SIZE + pixelColumn, row * Define::TILE_TX_SIZE + pixelRow) == Define::DATA_COLOR_MOUNTAINS)
					{
						mountainPixels++;
					}
					else if (_terrainData.getPixel(column * Define::TILE_TX_SIZE + pixelColumn, row * Define::TILE_TX_SIZE + pixelRow) == Define::DATA_COLOR_FOREST)
					{
						forestPixels++;
					}
					else
					{
						std::cout << "WRONG COLOR DETECTED!\n";
					}
				}
			}

			double totalPixels = Define::TILE_TX_SIZE * Define::TILE_TX_SIZE;

			double waterRatio = waterPixels / totalPixels;
			double flatgroundRatio = flatgroundPixels / totalPixels;
			double hillsRatio = hillPixels / totalPixels;
			double mountainsRatio = mountainPixels / totalPixels;
			double forestRatio = forestPixels / totalPixels;

			_tileTerrains.at(Terrain::Water)[_tileMatrix[row][column]] = waterRatio;
			_tileTerrains.at(Terrain::FlatGround)[_tileMatrix[row][column]] = flatgroundRatio;
			_tileTerrains.at(Terrain::Hills)[_tileMatrix[row][column]] = hillsRatio;
			_tileTerrains.at(Terrain::Mountains)[_tileMatrix[row][column]] = mountainsRatio;
			_tileTerrains.at(Terrain::Forest)[_tileMatrix[row][column]] = forestRatio;
		}
	}
}

/*int WorldMap::terrainPixelsInTile(int tileX, int tileY, Terrain terrain)
{
	int terrainPixels(0);
	sf::Color terrainColor;

	switch (terrain)
	{
		case Terrain::Water:
			terrainColor = Define::DATA_COLOR_WATER;
			break;

		case Terrain::FlatGround:
			terrainColor = Define::DATA_COLOR_FLATGROUND;
			break;

		case Terrain::Hills:
			terrainColor = Define::DATA_COLOR_HILLS;
			break;

		case Terrain::Mountains:
			terrainColor = Define::DATA_COLOR_MOUNTAINS;
			break;

		case Terrain::Forest:
			terrainColor = Define::DATA_COLOR_FOREST;
			break;
	}

	for (int pixelRow = 0; pixelRow < Define::TILE_TX_SIZE; pixelRow++)
	{
		for (int pixelColumn = 0; pixelColumn < Define::TILE_TX_SIZE; pixelColumn++)
		{
			if (_terrainData.getPixel(tileX * Define::TILE_TX_SIZE + pixelColumn, tileY * Define::TILE_TX_SIZE + pixelRow) == terrainColor)
			{
				terrainPixels++;
			}
		}
	}

	return terrainPixels;
}*/

void WorldMap::changeMapMode(Terrain mapMode)
{
	sf::Color baseColor;

	switch (mapMode)
	{
		case Terrain::Default:
			_backgroundTexture = _data->assets.getTexture("World Map Background");
			baseColor = Colors::MAP_MODE_DEFAULT;
			break;

		case Terrain::Water:
			_backgroundTexture = _data->assets.getTexture("World Map Background Grayscale");
			baseColor = Colors::MAP_MODE_WATER;
			break;

		case Terrain::FlatGround:
			_backgroundTexture = _data->assets.getTexture("World Map Background Grayscale");
			baseColor = Colors::MAP_MODE_FLATGROUND;
			break;

		case Terrain::Hills:
			_backgroundTexture = _data->assets.getTexture("World Map Background Grayscale");
			baseColor = Colors::MAP_MODE_HILLS;
			break;

		case Terrain::Mountains:
			_backgroundTexture = _data->assets.getTexture("World Map Background Grayscale");
			baseColor = Colors::MAP_MODE_MOUNTAINS;
			break;

		case Terrain::Forest:
			_backgroundTexture = _data->assets.getTexture("World Map Background Grayscale");
			baseColor = Colors::MAP_MODE_FOREST;
			break;
	}

	int differenceRed = 255 - baseColor.r;
	int differenceGreen = 255 - baseColor.g;
	int differenceBlue = 255 - baseColor.b;

	for (int row = 0; row < Define::WORLD_SIZE; row++)
	{
		for (int column = 0; column < Define::WORLD_SIZE; column++)
		{
			int quadIndex = _tileMatrix[row][column] * 4;

			for (int i = 0; i < 4; i++)
			{
				if (mapMode == Terrain::Default)
				{
					_vertices[quadIndex + i].color = sf::Color(baseColor);
				}
				else
				{
					double currentTerrain = _tileTerrains.at(mapMode)[_tileMatrix[row][column]];
					_vertices[quadIndex + i].color = sf::Color(255 - differenceRed * currentTerrain, 255 - differenceGreen * currentTerrain, 255 - differenceBlue * currentTerrain);
				}
			}
		}
	}
}

int WorldMap::coordsToTile(sf::Vector2i worldCoords)
{
	return _tileMatrix[worldCoords.y / Define::TILE_SIZE][worldCoords.x / Define::TILE_SIZE];
}