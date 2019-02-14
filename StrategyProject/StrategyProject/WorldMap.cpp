#include "stdafx.h"
#include "WorldMap.h"
#include "Defines.h"
#include <vector>
#include "SFML\Graphics.hpp"
#include <iostream>
#include "TileDataBoxState.h"

WorldMap::WorldMap(GameDataRef data)
	: _data(data),
	_tileMatrix(Define::WORLD_SIZE_IN_TILES_Y, std::vector<int>(Define::WORLD_SIZE_IN_TILES_X)),
	_vertices(sf::Quads, Define::WORLD_SIZE_IN_TILES_X * Define::WORLD_SIZE_IN_TILES_Y * 4),
	_view(sf::Vector2f(Define::WORLD_VIEW_WIDTH / 2, Define::WORLD_VIEW_HEIGHT / 2), sf::Vector2f(Define::WORLD_VIEW_WIDTH, Define::WORLD_VIEW_HEIGHT))
{
	_tileTerrains[Terrain::Water].resize(Define::WORLD_SIZE_IN_TILES_X * Define::WORLD_SIZE_IN_TILES_Y);
	_tileTerrains[Terrain::FlatGround].resize(Define::WORLD_SIZE_IN_TILES_X * Define::WORLD_SIZE_IN_TILES_Y);
	_tileTerrains[Terrain::Hills].resize(Define::WORLD_SIZE_IN_TILES_X * Define::WORLD_SIZE_IN_TILES_Y);
	_tileTerrains[Terrain::Mountains].resize(Define::WORLD_SIZE_IN_TILES_X * Define::WORLD_SIZE_IN_TILES_Y);
	_tileTerrains[Terrain::Forest].resize(Define::WORLD_SIZE_IN_TILES_X * Define::WORLD_SIZE_IN_TILES_Y);
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

	for (int row = 0; row < Define::WORLD_SIZE_IN_TILES_Y; row++)
	{
		for (int column = 0; column < Define::WORLD_SIZE_IN_TILES_X; column++)
		{
			_tileMatrix[row][column] = row * Define::WORLD_SIZE_IN_TILES_X + column;
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
	std::cout << "Loaded " << Define::WORLD_SIZE_IN_TILES_X * Define::WORLD_SIZE_IN_TILES_Y << " tiles in " << end - start << " seconds.\n";
}

void WorldMap::handleInput()
{
	sf::Event event;

	while (_data->window.pollEvent(event))
	{
		bool eventHandled = false;

		std::list<subStateRef>::reverse_iterator rit;

		for (rit = _subStates.rbegin(); rit != _subStates.rend() && !eventHandled; rit++)
		{
			eventHandled = (*rit)->handleInput(event);
		}

		if (!eventHandled)
		{
			if (event.type == sf::Event::Closed)
			{
				_data->window.close();
			}

			if (event.type == sf::Event::MouseButtonPressed)
			{
				handleMousePressEvent(event);
			}

			if (event.type == sf::Event::MouseWheelScrolled)
			{
				handleMouseScrollEvent(event);
			}

			if (event.type == sf::Event::KeyPressed)
			{
				handleKeyPressEvent(event);
			}
		}
	}

	handleRealTimeKeyPressInput();
}

void WorldMap::handleMousePressEvent(sf::Event &event)
{
	if (event.mouseButton.button == sf::Mouse::Left)
	{
		sf::Vector2i worldMouse(_data->window.mapPixelToCoords(sf::Mouse::getPosition(_data->window), _view).x, _data->window.mapPixelToCoords(sf::Mouse::getPosition(_data->window), _view).y);
		std::cout << "World Mouse: " << worldMouse.x << "," << worldMouse.y << "\n";

		int tileClicked(coordsToTile(worldMouse));
		std::map<Terrain, double> tileTerrainData;

		for (std::map<Terrain, std::vector<double>>::iterator it = _tileTerrains.begin(); it != _tileTerrains.end(); it++)
		{
			tileTerrainData[it->first] = _tileTerrains.at(it->first)[tileClicked];
		}

		_subStates.push_back(std::move(subStateRef(new TileDataBoxState(_data, tileTerrainData))));
		_subStates.back()->init();
	}
}
void WorldMap::handleMouseScrollEvent(sf::Event &event)
{
	if (event.mouseWheelScroll.delta >= 0)
	{
		if (_view.getSize().x < Define::WORLD_VIEW_WIDTH * 1 / Define::WORLD_CAMERA_MIN_ZOOM_FACTOR
			&& _view.getSize().y < Define::WORLD_VIEW_HEIGHT * 1 / Define::WORLD_CAMERA_MIN_ZOOM_FACTOR)
		{
			if (_view.getCenter().y - _view.getSize().y / 2 > 0 - Define::WORLD_CAMERA_EDGE_MARGIN
				&& _view.getCenter().y + _view.getSize().y / 2 < Define::WORLD_SIZE_IN_TILES_Y * Define::TILE_SIZE + Define::WORLD_CAMERA_EDGE_MARGIN
				&& _view.getCenter().x - _view.getSize().x / 2 > 0 - Define::WORLD_CAMERA_EDGE_MARGIN
				&& _view.getCenter().x + _view.getSize().x / 2 < Define::WORLD_SIZE_IN_TILES_X * Define::TILE_SIZE + Define::WORLD_CAMERA_EDGE_MARGIN)
			{
				_view.zoom(Define::WORLD_CAMERA_ZOOM_FACTOR);
			}
		}
	}
	else
	{
		if (_view.getSize().x > Define::WORLD_VIEW_WIDTH * 1 / Define::WORLD_CAMERA_MAX_ZOOM_FACTOR
			&& _view.getSize().y > Define::WORLD_VIEW_HEIGHT * 1 / Define::WORLD_CAMERA_MAX_ZOOM_FACTOR)
		{
			_view.zoom(1 / Define::WORLD_CAMERA_ZOOM_FACTOR);
		}
	}
}
void WorldMap::handleKeyPressEvent(sf::Event &event)
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
void WorldMap::handleRealTimeKeyPressInput()
{
	if (sf::Keyboard::isKeyPressed(Controls::CAMERA_MOVE_UP))
	{
		if (_view.getCenter().y - _view.getSize().y / 2 > 0 - Define::WORLD_CAMERA_EDGE_MARGIN)
		{
			_view.move(0.f, -Define::WORLD_CAMERA_MOVE_SPEED);
		}
	}
	if (sf::Keyboard::isKeyPressed(Controls::CAMERA_MOVE_DOWN))
	{
		if (_view.getCenter().y + _view.getSize().y / 2 < Define::WORLD_SIZE_IN_TILES_Y * Define::TILE_SIZE + Define::WORLD_CAMERA_EDGE_MARGIN)
		{
			_view.move(0.f, Define::WORLD_CAMERA_MOVE_SPEED);
		}
	}
	if (sf::Keyboard::isKeyPressed(Controls::CAMERA_MOVE_LEFT))
	{
		if (_view.getCenter().x - _view.getSize().x / 2 > 0 - Define::WORLD_CAMERA_EDGE_MARGIN)
		{
			_view.move(-Define::WORLD_CAMERA_MOVE_SPEED, 0.f);
		}
	}
	if (sf::Keyboard::isKeyPressed(Controls::CAMERA_MOVE_RIGHT))
	{
		if (_view.getCenter().x + _view.getSize().x / 2 < Define::WORLD_SIZE_IN_TILES_X * Define::TILE_SIZE + Define::WORLD_CAMERA_EDGE_MARGIN)
		{
			_view.move(Define::WORLD_CAMERA_MOVE_SPEED, 0.f);
		}
	}
}

void WorldMap::update(float delta)
{
	std::list<subStateRef>::reverse_iterator rit = _subStates.rbegin();

	while (rit != _subStates.rend())
	{
		if ((*rit)->remove())
		{
			rit = decltype(rit)(_subStates.erase(std::next(rit).base()));
		}
		else if ((*rit)->moveToTop() && rit != _subStates.rbegin())
		{
			subStateRef temp = std::move(*rit);
			rit = decltype(rit)(_subStates.erase(std::next(rit).base()));
			_subStates.push_back(std::move(temp));
			_subStates.back()->update(delta);
		}
		else
		{
			(*rit)->update(delta);
			rit++;
		}
		
	}
}

void WorldMap::draw()
{
	_data->window.clear(sf::Color(sf::Color::White));

	_data->window.setView(_view);

	_data->window.draw(_vertices, &_backgroundTexture);

	for (auto &subState : _subStates)
	{
		subState->draw();
	}

	_data->window.display();
}

void WorldMap::loadTerrainData()
{
	std::cout << "Load Terrain Data...\n";
	for (int row = 0; row < Define::WORLD_SIZE_IN_TILES_Y; row++)
	{
		for (int column = 0; column < Define::WORLD_SIZE_IN_TILES_X; column++)
		{
			loadTerrainDataForTile(column, row);
		}
	}
}

void WorldMap::loadTerrainDataForTile(int tileX, int tileY)
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
			if (_terrainData.getPixel(tileX * Define::TILE_TX_SIZE + pixelColumn, tileY * Define::TILE_TX_SIZE + pixelRow) == Define::DATA_COLOR_WATER)
			{
				waterPixels++;
			}
			else if (_terrainData.getPixel(tileX * Define::TILE_TX_SIZE + pixelColumn, tileY * Define::TILE_TX_SIZE + pixelRow) == Define::DATA_COLOR_FLATGROUND)
			{
				flatgroundPixels++;
			}
			else if (_terrainData.getPixel(tileX * Define::TILE_TX_SIZE + pixelColumn, tileY * Define::TILE_TX_SIZE + pixelRow) == Define::DATA_COLOR_HILLS)
			{
				hillPixels++;
			}
			else if (_terrainData.getPixel(tileX * Define::TILE_TX_SIZE + pixelColumn, tileY * Define::TILE_TX_SIZE + pixelRow) == Define::DATA_COLOR_MOUNTAINS)
			{
				mountainPixels++;
			}
			else if (_terrainData.getPixel(tileX * Define::TILE_TX_SIZE + pixelColumn, tileY * Define::TILE_TX_SIZE + pixelRow) == Define::DATA_COLOR_FOREST)
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

	_tileTerrains.at(Terrain::Water)[_tileMatrix[tileY][tileX]] = waterRatio;
	_tileTerrains.at(Terrain::FlatGround)[_tileMatrix[tileY][tileX]] = flatgroundRatio;
	_tileTerrains.at(Terrain::Hills)[_tileMatrix[tileY][tileX]] = hillsRatio;
	_tileTerrains.at(Terrain::Mountains)[_tileMatrix[tileY][tileX]] = mountainsRatio;
	_tileTerrains.at(Terrain::Forest)[_tileMatrix[tileY][tileX]] = forestRatio;
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
	_backgroundTexture = _data->assets.getTexture("World Map Background Grayscale");

	switch (mapMode)
	{
		case Terrain::Water:
			baseColor = Colors::MAP_MODE_WATER;
			break;

		case Terrain::FlatGround:
			baseColor = Colors::MAP_MODE_FLATGROUND;
			break;

		case Terrain::Hills:
			baseColor = Colors::MAP_MODE_HILLS;
			break;

		case Terrain::Mountains:
			baseColor = Colors::MAP_MODE_MOUNTAINS;
			break;

		case Terrain::Forest:
			baseColor = Colors::MAP_MODE_FOREST;
			break;

		default:
			_backgroundTexture = _data->assets.getTexture("World Map Background");
			baseColor = Colors::MAP_MODE_DEFAULT;
	}

	int differenceRed = 255 - baseColor.r;
	int differenceGreen = 255 - baseColor.g;
	int differenceBlue = 255 - baseColor.b;

	for (int row = 0; row < Define::WORLD_SIZE_IN_TILES_Y; row++)
	{
		for (int column = 0; column < Define::WORLD_SIZE_IN_TILES_X; column++)
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