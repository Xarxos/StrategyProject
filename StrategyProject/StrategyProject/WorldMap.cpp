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
	_view(sf::Vector2f(Define::WORLD_VIEW_WIDTH / 2, Define::WORLD_VIEW_HEIGHT / 2), sf::Vector2f(Define::WORLD_VIEW_WIDTH, Define::WORLD_VIEW_HEIGHT)),
	_selectedTile(sf::Vector2f(Define::TILE_SIZE, Define::TILE_SIZE)),
	_tileIsSelected(false)
{
	_tileTerrainRatios[Terrain::Water].resize(Define::WORLD_SIZE_IN_TILES_X * Define::WORLD_SIZE_IN_TILES_Y);
	_tileTerrainRatios[Terrain::FlatGround].resize(Define::WORLD_SIZE_IN_TILES_X * Define::WORLD_SIZE_IN_TILES_Y);
	_tileTerrainRatios[Terrain::Hills].resize(Define::WORLD_SIZE_IN_TILES_X * Define::WORLD_SIZE_IN_TILES_Y);
	_tileTerrainRatios[Terrain::Mountains].resize(Define::WORLD_SIZE_IN_TILES_X * Define::WORLD_SIZE_IN_TILES_Y);
	_tileTerrainRatios[Terrain::Forest].resize(Define::WORLD_SIZE_IN_TILES_X * Define::WORLD_SIZE_IN_TILES_Y);
}

void WorldMap::init()
{
	std::cout << "Start init().\n";
	sf::Clock clock;
	float start = clock.getElapsedTime().asSeconds();

	loadAssets();

	for (int row = 0; row < Define::WORLD_SIZE_IN_TILES_Y; row++)
	{
		for (int column = 0; column < Define::WORLD_SIZE_IN_TILES_X; column++)
		{
			initializeTile(column, row);
		}
	}

	_selectedTile.setFillColor(sf::Color(255, 255, 255, 0));
	_selectedTile.setOutlineColor(Colors::TILE_SELECT_HIGHLIGHT_COLOR);
	_selectedTile.setOutlineThickness(Define::TILE_SELECT_OUTLINE_THICKNESS);

	loadTerrainData();

	float end = clock.getElapsedTime().asSeconds();
	std::cout << "Loaded " << Define::WORLD_SIZE_IN_TILES_X * Define::WORLD_SIZE_IN_TILES_Y << " tiles in " << end - start << " seconds.\n";
}

void WorldMap::loadAssets()
{
	_data->assets.loadImage("World Map Terrain Data", Filepath::WORLD_MAP_BACKGROUND);
	_data->assets.loadTexture("World Map Background", Filepath::WORLD_MAP_BACKGROUND);
	_data->assets.loadTexture("World Map Background Grayscale", Filepath::WORLD_MAP_BACKGROUND_GRAYSCALE);

	_backgroundTexture = _data->assets.getTexture("World Map Background");
	_terrainData = _data->assets.getImage("World Map Terrain Data");
}

void WorldMap::initializeTile(int tileX, int tileY)
{
	_tileMatrix[tileY][tileX] = tileY * Define::WORLD_SIZE_IN_TILES_X + tileX;
	int quadIndex = _tileMatrix[tileY][tileX] * 4;

	_vertices[quadIndex + 0].position = sf::Vector2f(tileX * Define::TILE_SIZE, tileY * Define::TILE_SIZE);
	_vertices[quadIndex + 1].position = sf::Vector2f(tileX * Define::TILE_SIZE + Define::TILE_SIZE, tileY * Define::TILE_SIZE);
	_vertices[quadIndex + 2].position = sf::Vector2f(tileX * Define::TILE_SIZE + Define::TILE_SIZE, tileY * Define::TILE_SIZE + Define::TILE_SIZE);
	_vertices[quadIndex + 3].position = sf::Vector2f(tileX * Define::TILE_SIZE, tileY * Define::TILE_SIZE + Define::TILE_SIZE);

	_vertices[quadIndex + 0].color = sf::Color(sf::Color::Green);
	_vertices[quadIndex + 1].color = sf::Color(sf::Color::Red);
	_vertices[quadIndex + 2].color = sf::Color(sf::Color::Blue);
	_vertices[quadIndex + 3].color = sf::Color(sf::Color::Magenta);

	_vertices[quadIndex + 0].texCoords = sf::Vector2f(tileX * Define::TILE_TX_SIZE, tileY * Define::TILE_TX_SIZE);
	_vertices[quadIndex + 1].texCoords = sf::Vector2f(tileX * Define::TILE_TX_SIZE + Define::TILE_TX_SIZE, tileY * Define::TILE_TX_SIZE);
	_vertices[quadIndex + 2].texCoords = sf::Vector2f(tileX * Define::TILE_TX_SIZE + Define::TILE_TX_SIZE, tileY * Define::TILE_TX_SIZE + Define::TILE_TX_SIZE);
	_vertices[quadIndex + 3].texCoords = sf::Vector2f(tileX * Define::TILE_TX_SIZE, tileY * Define::TILE_TX_SIZE + Define::TILE_TX_SIZE);
}

void WorldMap::loadTerrainData()
{
	std::cout << "Load Terrain Data...\n";
	for (int row = 0; row < Define::WORLD_SIZE_IN_TILES_Y; row++)
	{
		for (int column = 0; column < Define::WORLD_SIZE_IN_TILES_X; column++)
		{
			//std::cout << "Row: " << row << ", Column: " << column << "\n";
			loadTerrainDataForTile(column, row);
		}
	}
	std::cout << "Loaded Terrain Data.\n";
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
		//std::cout << "PixelRow: " << pixelRow << "\n";
		for (int pixelColumn = 0; pixelColumn < Define::TILE_TX_SIZE; pixelColumn++)
		{
			//", PixelColumn: " << pixelColumn <<
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
	//std::cout << "After pixel loops.\n";
	double totalPixels = Define::TILE_TX_SIZE * Define::TILE_TX_SIZE;

	double waterRatio = waterPixels / totalPixels;
	double flatgroundRatio = flatgroundPixels / totalPixels;
	double hillsRatio = hillPixels / totalPixels;
	double mountainsRatio = mountainPixels / totalPixels;
	double forestRatio = forestPixels / totalPixels;

	_tileTerrainRatios.at(Terrain::Water)[_tileMatrix[tileY][tileX]] = waterRatio;
	_tileTerrainRatios.at(Terrain::FlatGround)[_tileMatrix[tileY][tileX]] = flatgroundRatio;
	_tileTerrainRatios.at(Terrain::Hills)[_tileMatrix[tileY][tileX]] = hillsRatio;
	_tileTerrainRatios.at(Terrain::Mountains)[_tileMatrix[tileY][tileX]] = mountainsRatio;
	_tileTerrainRatios.at(Terrain::Forest)[_tileMatrix[tileY][tileX]] = forestRatio;
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
		sf::Vector2i tileClicked(coordsToTile(worldMouse).x, coordsToTile(worldMouse).y);

		if (tileClicked.x != -1)
		{
			int tileClickedIndex = _tileMatrix[tileClicked.y][tileClicked.x];

			std::map<Terrain, double> tileTerrainData;

			for (std::map<Terrain, std::vector<double>>::iterator it = _tileTerrainRatios.begin(); it != _tileTerrainRatios.end(); it++)
			{
				tileTerrainData[it->first] = _tileTerrainRatios.at(it->first)[tileClickedIndex];
			}

			_subStates.push_back(std::move(subStateRef(new TileDataBoxState(_data, tileClicked, tileTerrainData))));
			_subStates.back()->init();
		}
	}
}
void WorldMap::handleMouseScrollEvent(sf::Event &event)
{
	if (event.mouseWheelScroll.delta >= 0)
	{
		if (_view.getSize().x < Define::WORLD_VIEW_WIDTH * 1 / Define::WORLD_CAMERA_MIN_ZOOM_FACTOR
			&& _view.getSize().y < Define::WORLD_VIEW_HEIGHT * 1 / Define::WORLD_CAMERA_MIN_ZOOM_FACTOR)
		{
			/*if (_view.getCenter().y - _view.getSize().y / 2 > 0 - Define::WORLD_CAMERA_EDGE_MARGIN
				&& _view.getCenter().y + _view.getSize().y / 2 < Define::WORLD_SIZE_IN_TILES_Y * Define::TILE_SIZE + Define::WORLD_CAMERA_EDGE_MARGIN
				&& _view.getCenter().x - _view.getSize().x / 2 > 0 - Define::WORLD_CAMERA_EDGE_MARGIN
				&& _view.getCenter().x + _view.getSize().x / 2 < Define::WORLD_SIZE_IN_TILES_X * Define::TILE_SIZE + Define::WORLD_CAMERA_EDGE_MARGIN)
			{*/
				_view.zoom(Define::WORLD_CAMERA_ZOOM_FACTOR);
			//}

			/*float actualCameraEdgeRelativeToAllowedCameraEdge = (0 - Define::WORLD_CAMERA_EDGE_MARGIN) - (_view.getCenter().y - _view.getSize().y / 2);		// I really wish I could think of a more concise name for this variable...
			if (actualCameraEdgeRelativeToAllowedCameraEdge < 0)
			{
				_view.setCenter(_view.getCenter().x, _view.getCenter().y + actualCameraEdgeRelativeToAllowedCameraEdge));
			}*/
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
		_view.move(0.f, -Define::WORLD_CAMERA_MOVE_SPEED);
	}
	if (sf::Keyboard::isKeyPressed(Controls::CAMERA_MOVE_DOWN))
	{
		_view.move(0.f, Define::WORLD_CAMERA_MOVE_SPEED);
	}
	if (sf::Keyboard::isKeyPressed(Controls::CAMERA_MOVE_LEFT))
	{
		_view.move(-Define::WORLD_CAMERA_MOVE_SPEED, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(Controls::CAMERA_MOVE_RIGHT))
	{
		_view.move(Define::WORLD_CAMERA_MOVE_SPEED, 0.f);
	}
}

void WorldMap::update(float delta)
{
	updateSubStates(delta);
	
	checkTileSelection();

	correctCameraView();
}

void WorldMap::updateSubStates(float delta)
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

void WorldMap::checkTileSelection()
{
	if (!_subStates.empty())
	{
		TileDataBoxState* topSubStateIsDataBox = dynamic_cast<TileDataBoxState*>(_subStates.back().get());

		if (topSubStateIsDataBox)
		{
			topSubStateIsDataBox->selectBox(true);
			_selectedTile.setPosition(topSubStateIsDataBox->getTileCoords().x * Define::TILE_SIZE, topSubStateIsDataBox->getTileCoords().y * Define::TILE_SIZE);
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
void WorldMap::correctCameraView()
{
	if (_view.getCenter().y - _view.getSize().y / 2 < 0 - Define::WORLD_CAMERA_EDGE_MARGIN)
	{
		_view.move(0.f, Define::WORLD_CAMERA_MOVE_SPEED);
	}

	if (_view.getCenter().y + _view.getSize().y / 2 > Define::WORLD_SIZE_IN_TILES_Y * Define::TILE_SIZE + Define::WORLD_CAMERA_EDGE_MARGIN)
	{
		_view.move(0.f, -Define::WORLD_CAMERA_MOVE_SPEED);
	}

	if (_view.getCenter().x - _view.getSize().x / 2 < 0 - Define::WORLD_CAMERA_EDGE_MARGIN)
	{
		_view.move(Define::WORLD_CAMERA_MOVE_SPEED, 0.f);
	}

	if (_view.getCenter().x + _view.getSize().x / 2 > Define::WORLD_SIZE_IN_TILES_X * Define::TILE_SIZE + Define::WORLD_CAMERA_EDGE_MARGIN)
	{
		_view.move(-Define::WORLD_CAMERA_MOVE_SPEED, 0.f);
	}
}

void WorldMap::draw()
{
	_data->window.clear(sf::Color(sf::Color::White));

	_data->window.setView(_view);

	_data->window.draw(_vertices, &_backgroundTexture);

	if (_tileIsSelected)
	{
		_data->window.draw(_selectedTile);
	}

	for (auto &subState : _subStates)
	{
		subState->draw();
	}

	_data->window.display();
}

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
					double currentTerrainRatio = _tileTerrainRatios.at(mapMode)[_tileMatrix[row][column]];
					_vertices[quadIndex + i].color = sf::Color(255 - differenceRed * currentTerrainRatio, 255 - differenceGreen * currentTerrainRatio, 255 - differenceBlue * currentTerrainRatio);
				}
			}
		}
	}
}

sf::Vector2i WorldMap::coordsToTile(sf::Vector2i worldCoords)
{
	if (!_vertices.getBounds().contains(worldCoords.x, worldCoords.y))
	{
		return sf::Vector2i(-1, -1);
	}

	return sf::Vector2i(worldCoords.x / Define::TILE_SIZE, worldCoords.y / Define::TILE_SIZE);
}