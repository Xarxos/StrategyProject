#include "stdafx.h"
#include "WorldMap.h"
#include "RegionMap.h"
#include "Defines.h"
#include <vector>
#include "SFML\Graphics.hpp"
#include <iostream>
#include "TileDataBoxState.h"
#include "HUD.h"
#include "GameDatabase.h"

RegionMap::RegionMap(EngineDataRef engineData, DatabaseRef database)
	: _engine(engineData),
	_database(database),
	_tileMatrix(Define::REGION_SIZE_IN_TILES_Y, std::vector<int>(Define::REGION_SIZE_IN_TILES_X)),
	_vertices(sf::Quads, Define::REGION_SIZE_IN_TILES_X * Define::REGION_SIZE_IN_TILES_Y * 4),
	_HUD(engineData, database),
	_mainView(sf::Vector2f(Define::REGION_VIEW_WIDTH / 2, Define::REGION_VIEW_HEIGHT / 2), sf::Vector2f(Define::REGION_VIEW_WIDTH, Define::REGION_VIEW_HEIGHT)),
	_miniMapView(sf::Vector2f(Define::REGION_SIZE_IN_TILES_X * Define::REGION_TILE_SIZE / 2, Define::REGION_SIZE_IN_TILES_Y * Define::REGION_TILE_SIZE / 2), sf::Vector2f(Define::REGION_SIZE_IN_TILES_X * Define::REGION_TILE_SIZE, Define::REGION_SIZE_IN_TILES_Y * Define::REGION_TILE_SIZE)),
	_selectedTile(sf::Vector2f(Define::REGION_TILE_SIZE, Define::REGION_TILE_SIZE)),
	_tileIsSelected(false)
{
	
}

void RegionMap::init()
{
	std::cout << "Start init().\n";
	sf::Clock clock;
	float start = clock.getElapsedTime().asSeconds();

	loadAssets();

	_HUD.init();
	_miniMapView.setViewport(sf::FloatRect(1 - Define::MINIMAP_SIZE_FACTOR, 1 - Define::MINIMAP_SIZE_FACTOR, Define::MINIMAP_SIZE_FACTOR, Define::MINIMAP_SIZE_FACTOR));

	for (int row = 0; row < Define::REGION_SIZE_IN_TILES_Y; row++)
	{
		for (int column = 0; column < Define::REGION_SIZE_IN_TILES_X; column++)
		{
			initializeTile(column, row);
		}
	}

	_selectedTile.setFillColor(sf::Color(255, 255, 255, 0));
	_selectedTile.setOutlineColor(Colors::TILE_SELECT_HIGHLIGHT_COLOR);
	_selectedTile.setOutlineThickness(Define::TILE_SELECT_OUTLINE_THICKNESS);

	loadTerrainData();

	float end = clock.getElapsedTime().asSeconds();
	std::cout << "Loaded " << Define::REGION_SIZE_IN_TILES_X * Define::REGION_SIZE_IN_TILES_Y << " tiles in " << end - start << " seconds.\n";
}

void RegionMap::loadAssets()
{
	_engine->assets.loadImage("Region 1 Terrain Data", Filepath::REGION1_MAP_BACKGROUND);
	_engine->assets.loadTexture("Region 1 Background", Filepath::REGION1_MAP_BACKGROUND);
	_engine->assets.loadTexture("Region 1 Background Grayscale", Filepath::REGION1_MAP_BACKGROUND_GRAYSCALE);

	_backgroundTexture = _engine->assets.getTexture("Region 1 Background");
	_terrainData = _engine->assets.getImage("Region 1 Terrain Data");
}

void RegionMap::initializeTile(int tileX, int tileY)
{
	_tileMatrix[tileY][tileX] = tileY * Define::REGION_SIZE_IN_TILES_X + tileX;
	int quadIndex = _tileMatrix[tileY][tileX] * 4;

	_vertices[quadIndex + 0].position = sf::Vector2f(tileX * Define::REGION_TILE_SIZE, tileY * Define::REGION_TILE_SIZE);
	_vertices[quadIndex + 1].position = sf::Vector2f(tileX * Define::REGION_TILE_SIZE + Define::REGION_TILE_SIZE, tileY * Define::REGION_TILE_SIZE);
	_vertices[quadIndex + 2].position = sf::Vector2f(tileX * Define::REGION_TILE_SIZE + Define::REGION_TILE_SIZE, tileY * Define::REGION_TILE_SIZE + Define::REGION_TILE_SIZE);
	_vertices[quadIndex + 3].position = sf::Vector2f(tileX * Define::REGION_TILE_SIZE, tileY * Define::REGION_TILE_SIZE + Define::REGION_TILE_SIZE);

	_vertices[quadIndex + 0].color = sf::Color(sf::Color::Green);
	_vertices[quadIndex + 1].color = sf::Color(sf::Color::Red);
	_vertices[quadIndex + 2].color = sf::Color(sf::Color::Blue);
	_vertices[quadIndex + 3].color = sf::Color(sf::Color::Magenta);

	_vertices[quadIndex + 0].texCoords = sf::Vector2f(tileX * Define::REGION_TILE_TX_SIZE, tileY * Define::REGION_TILE_TX_SIZE);
	_vertices[quadIndex + 1].texCoords = sf::Vector2f(tileX * Define::REGION_TILE_TX_SIZE + Define::REGION_TILE_TX_SIZE, tileY * Define::REGION_TILE_TX_SIZE);
	_vertices[quadIndex + 2].texCoords = sf::Vector2f(tileX * Define::REGION_TILE_TX_SIZE + Define::REGION_TILE_TX_SIZE, tileY * Define::REGION_TILE_TX_SIZE + Define::REGION_TILE_TX_SIZE);
	_vertices[quadIndex + 3].texCoords = sf::Vector2f(tileX * Define::REGION_TILE_TX_SIZE, tileY * Define::REGION_TILE_TX_SIZE + Define::REGION_TILE_TX_SIZE);
}

void RegionMap::loadTerrainData()
{
	std::cout << "Load Terrain Data...\n";
	for (int row = 0; row < Define::REGION_SIZE_IN_TILES_Y; row++)
	{
		for (int column = 0; column < Define::REGION_SIZE_IN_TILES_X; column++)
		{
			loadTerrainDataForTile(column, row);
		}
	}
	std::cout << "Loaded Terrain Data.\n";
}

void RegionMap::loadTerrainDataForTile(int tileX, int tileY)
{
	int waterPixels(0);
	int flatgroundPixels(0);
	int hillPixels(0);
	int mountainPixels(0);
	int forestPixels(0);

	for (int pixelRow = 0; pixelRow < Define::REGION_TILE_TX_SIZE; pixelRow++)
	{
		for (int pixelColumn = 0; pixelColumn < Define::REGION_TILE_TX_SIZE; pixelColumn++)
		{
			if (_terrainData.getPixel(tileX * Define::REGION_TILE_TX_SIZE + pixelColumn, tileY * Define::REGION_TILE_TX_SIZE + pixelRow) == Define::DATA_COLOR_WATER)
			{
				waterPixels++;
			}
			else if (_terrainData.getPixel(tileX * Define::REGION_TILE_TX_SIZE + pixelColumn, tileY * Define::REGION_TILE_TX_SIZE + pixelRow) == Define::DATA_COLOR_FLATGROUND)
			{
				flatgroundPixels++;
			}
			else if (_terrainData.getPixel(tileX * Define::REGION_TILE_TX_SIZE + pixelColumn, tileY * Define::REGION_TILE_TX_SIZE + pixelRow) == Define::DATA_COLOR_HILLS)
			{
				hillPixels++;
			}
			else if (_terrainData.getPixel(tileX * Define::REGION_TILE_TX_SIZE + pixelColumn, tileY * Define::REGION_TILE_TX_SIZE + pixelRow) == Define::DATA_COLOR_MOUNTAINS)
			{
				mountainPixels++;
			}
			else if (_terrainData.getPixel(tileX * Define::REGION_TILE_TX_SIZE + pixelColumn, tileY * Define::REGION_TILE_TX_SIZE + pixelRow) == Define::DATA_COLOR_FOREST)
			{
				forestPixels++;
			}
			else
			{
				//std::cout << "WRONG COLOR DETECTED!\n";
			}
		}
	}
	double totalPixels = Define::REGION_TILE_TX_SIZE * Define::REGION_TILE_TX_SIZE;

	double waterRatio = waterPixels / totalPixels;
	double flatgroundRatio = flatgroundPixels / totalPixels;
	double hillsRatio = hillPixels / totalPixels;
	double mountainsRatio = mountainPixels / totalPixels;
	double forestRatio = forestPixels / totalPixels;

	/*_tileTerrainRatios.at(Terrain::Water)[_tileMatrix[tileY][tileX]] = waterRatio;
	_tileTerrainRatios.at(Terrain::FlatGround)[_tileMatrix[tileY][tileX]] = flatgroundRatio;
	_tileTerrainRatios.at(Terrain::Hills)[_tileMatrix[tileY][tileX]] = hillsRatio;
	_tileTerrainRatios.at(Terrain::Mountains)[_tileMatrix[tileY][tileX]] = mountainsRatio;
	_tileTerrainRatios.at(Terrain::Forest)[_tileMatrix[tileY][tileX]] = forestRatio;*/
}

void RegionMap::handleInput()
{
	sf::Event event;

	while (_engine->window.pollEvent(event))
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
				_engine->window.close();
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

void RegionMap::handleMousePressEvent(sf::Event &event)
{
	if (event.mouseButton.button == sf::Mouse::Left)
	{
		sf::Vector2i worldMouse(_engine->window.mapPixelToCoords(sf::Mouse::getPosition(_engine->window), _mainView).x, _engine->window.mapPixelToCoords(sf::Mouse::getPosition(_engine->window), _mainView).y);
		sf::Vector2i tileClicked(coordsToTile(worldMouse).x, coordsToTile(worldMouse).y);

		if (tileClicked.x != -1)
		{
			int tileClickedIndex = _tileMatrix[tileClicked.y][tileClicked.x];

			/*std::map<Terrain, double> tileTerrainData;

			for (std::map<Terrain, std::vector<double>>::iterator it = _tileTerrainRatios.begin(); it != _tileTerrainRatios.end(); it++)
			{
				tileTerrainData[it->first] = _tileTerrainRatios.at(it->first)[tileClickedIndex];
			}*/

			//_subStates.push_back(std::move(subStateRef(new TileDataBoxState(_engine, _database, tileClicked, tileTerrainData))));
			_subStates.back()->init();
		}
	}
}
void RegionMap::handleMouseScrollEvent(sf::Event &event)
{
	if (event.mouseWheelScroll.delta >= 0)
	{
		if (_mainView.getSize().x < Define::REGION_VIEW_WIDTH * 1 / Define::REGION_CAMERA_MIN_ZOOM_FACTOR
			&& _mainView.getSize().y < Define::REGION_VIEW_HEIGHT * 1 / Define::REGION_CAMERA_MIN_ZOOM_FACTOR)
		{
			_mainView.zoom(Define::REGION_CAMERA_ZOOM_FACTOR);
		}
	}
	else
	{
		if (_mainView.getSize().x > Define::REGION_VIEW_WIDTH * 1 / Define::REGION_CAMERA_MAX_ZOOM_FACTOR
			&& _mainView.getSize().y > Define::REGION_VIEW_HEIGHT * 1 / Define::REGION_CAMERA_MAX_ZOOM_FACTOR)
		{
			_mainView.zoom(1 / Define::REGION_CAMERA_ZOOM_FACTOR);
		}
	}
}
void RegionMap::handleKeyPressEvent(sf::Event &event)
{
	/*if (event.key.code == Controls::WORLD_MAP_MODE_DEFAULT)
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
	}*/
}
void RegionMap::handleRealTimeKeyPressInput()
{
	if (sf::Keyboard::isKeyPressed(Controls::CAMERA_MOVE_UP))
	{
		_mainView.move(0.f, -Define::REGION_CAMERA_MOVE_SPEED);
	}
	if (sf::Keyboard::isKeyPressed(Controls::CAMERA_MOVE_DOWN))
	{
		_mainView.move(0.f, Define::REGION_CAMERA_MOVE_SPEED);
	}
	if (sf::Keyboard::isKeyPressed(Controls::CAMERA_MOVE_LEFT))
	{
		_mainView.move(-Define::REGION_CAMERA_MOVE_SPEED, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(Controls::CAMERA_MOVE_RIGHT))
	{
		_mainView.move(Define::REGION_CAMERA_MOVE_SPEED, 0.f);
	}
}

void RegionMap::update(float delta)
{
	updateSubStates(delta);

	checkTileSelection();

	correctCameraView();
}

void RegionMap::updateSubStates(float delta)
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
			TileDataBoxState* currentSubStateIsDataBox = dynamic_cast<TileDataBoxState*>((*rit).get());

			if (currentSubStateIsDataBox)
			{
				currentSubStateIsDataBox->selectBox(false);
			}

			(*rit)->update(delta);
			rit++;
		}
	}
}

void RegionMap::checkTileSelection()
{
	if (!_subStates.empty())
	{
		TileDataBoxState* topSubStateIsDataBox = dynamic_cast<TileDataBoxState*>(_subStates.back().get());

		if (topSubStateIsDataBox)
		{
			topSubStateIsDataBox->selectBox(true);
			_selectedTile.setPosition(topSubStateIsDataBox->getTileCoords().x * Define::REGION_TILE_SIZE, topSubStateIsDataBox->getTileCoords().y * Define::REGION_TILE_SIZE);
			_tileIsSelected = true;
		}
		else
		{
			_tileIsSelected = false;
		}
	}
	else
	{
		_tileIsSelected = false;
	}
}
// Putting a pin in this one!
void RegionMap::correctCameraView()
{
	if (_mainView.getCenter().y - _mainView.getSize().y / 2 < 0 - Define::REGION_CAMERA_EDGE_MARGIN)
	{
		_mainView.move(0.f, Define::REGION_CAMERA_MOVE_SPEED);
	}

	if (_mainView.getCenter().y + _mainView.getSize().y / 2 > Define::REGION_SIZE_IN_TILES_Y * Define::REGION_TILE_SIZE + Define::REGION_CAMERA_EDGE_MARGIN)
	{
		_mainView.move(0.f, -Define::REGION_CAMERA_MOVE_SPEED);
	}

	if (_mainView.getCenter().x - _mainView.getSize().x / 2 < 0 - Define::REGION_CAMERA_EDGE_MARGIN)
	{
		_mainView.move(Define::REGION_CAMERA_MOVE_SPEED, 0.f);
	}

	if (_mainView.getCenter().x + _mainView.getSize().x / 2 > Define::REGION_SIZE_IN_TILES_X * Define::REGION_TILE_SIZE + Define::REGION_CAMERA_EDGE_MARGIN)
	{
		_mainView.move(-Define::REGION_CAMERA_MOVE_SPEED, 0.f);
	}
}

void RegionMap::draw()
{
	_engine->window.clear(sf::Color(sf::Color::White));

	_engine->window.setView(_mainView);
	_engine->window.draw(_vertices, &_backgroundTexture);

	if (_tileIsSelected)
	{
		_engine->window.draw(_selectedTile);
	}

	for (auto &subState : _subStates)
	{
		subState->draw();
	}

	_HUD.draw();

	_engine->window.setView(_miniMapView);
	_engine->window.draw(_vertices, &_backgroundTexture);

	_engine->window.display();
}

/*void RegionMap::changeMapMode(Terrain mapMode)
{
	sf::Color baseColor;
	_backgroundTexture = _engine->assets.getTexture("Region 1 Background Grayscale");

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
		_backgroundTexture = _engine->assets.getTexture("Region 1 Background");
		baseColor = Colors::MAP_MODE_DEFAULT;
	}

	int differenceRed = 255 - baseColor.r;
	int differenceGreen = 255 - baseColor.g;
	int differenceBlue = 255 - baseColor.b;

	for (int row = 0; row < Define::REGION_SIZE_IN_TILES_Y; row++)
	{
		for (int column = 0; column < Define::REGION_SIZE_IN_TILES_X; column++)
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
					double currentTerrainRatio = _tileTerrainRatios.at(mapMode)[_tileMatrix[row][column]];
					_vertices[quadIndex + i].color = sf::Color(255 - differenceRed * currentTerrainRatio, 255 - differenceGreen * currentTerrainRatio, 255 - differenceBlue * currentTerrainRatio);
				}
			}
		}
	}
}*/

sf::Vector2i RegionMap::coordsToTile(sf::Vector2i worldCoords)
{
	if (!_vertices.getBounds().contains(worldCoords.x, worldCoords.y))
	{
		return sf::Vector2i(-1, -1);
	}

	return sf::Vector2i(worldCoords.x / Define::REGION_TILE_SIZE, worldCoords.y / Define::REGION_TILE_SIZE);
}