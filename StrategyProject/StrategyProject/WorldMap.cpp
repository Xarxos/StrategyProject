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
	_tileTerrains[MapMode::Water] =
	{
		0.05, 0.01, 0.08, 0.95, 0.01,
		0.02, 0.02, 0.03, 0.60, 0.40,
		0.65, 0.20, 0.10, 0.90, 0.65,
		0.35, 0.35, 0.25, 0.95, 0.10,
		0.15, 0.55, 0.85, 0.55, 0.07
	};
	/*_tiles.flatGround.resize(Define::WORLD_SIZE * Define::WORLD_SIZE);
	_tiles.hills.resize(Define::WORLD_SIZE * Define::WORLD_SIZE);
	_tiles.mountains.resize(Define::WORLD_SIZE * Define::WORLD_SIZE);
	_tiles.water.resize(Define::WORLD_SIZE * Define::WORLD_SIZE);
	_tiles.forest.resize(Define::WORLD_SIZE * Define::WORLD_SIZE);
	_tiles.grassLand.resize(Define::WORLD_SIZE * Define::WORLD_SIZE);
	_tiles.farmLand.resize(Define::WORLD_SIZE * Define::WORLD_SIZE);*/
}

void WorldMap::init()
{
	std::cout << "Start init().\n";
	sf::Clock clock;
	float start = clock.getElapsedTime().asSeconds();

	for (int row = 0; row < Define::WORLD_SIZE; row++)
	{
		for (int column = 0; column < Define::WORLD_SIZE; column++)
		{
			_tileMatrix[row][column] = row * Define::WORLD_SIZE + column;
			int quadIndex = _tileMatrix[row][column] * 4;

			_vertices[quadIndex + 0].position = sf::Vector2f(row * Define::TILE_SIZE, column * Define::TILE_SIZE);
			_vertices[quadIndex + 1].position = sf::Vector2f(row * Define::TILE_SIZE, column * Define::TILE_SIZE + Define::TILE_SIZE);
			_vertices[quadIndex + 2].position = sf::Vector2f(row * Define::TILE_SIZE + Define::TILE_SIZE, column * Define::TILE_SIZE + Define::TILE_SIZE);
			_vertices[quadIndex + 3].position = sf::Vector2f(row * Define::TILE_SIZE + Define::TILE_SIZE, column * Define::TILE_SIZE);

			_vertices[quadIndex + 0].color = sf::Color(sf::Color::Green);
			_vertices[quadIndex + 1].color = sf::Color(sf::Color::Red);
			_vertices[quadIndex + 2].color = sf::Color(sf::Color::Blue);
			_vertices[quadIndex + 3].color = sf::Color(sf::Color::Magenta);

			/*
			_vertices[quadIndex + 0].texCoords = sf::Vector2f(0.f, 0.f);
			_vertices[quadIndex + 1].texCoords = sf::Vector2f(Config::SQUARE_TX_SIZE, 0.f);
			_vertices[quadIndex + 2].texCoords = sf::Vector2f(Config::SQUARE_TX_SIZE, Config::SQUARE_TX_SIZE);
			_vertices[quadIndex + 3].texCoords = sf::Vector2f(0.f, Config::SQUARE_TX_SIZE);
			*/
		}
	}

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

		if (event.type == sf::Event::MouseWheelScrolled)
		{
			_view.setSize(_view.getSize().x - event.mouseWheelScroll.delta * Define::WORLD_CAMERA_ZOOM_FACTOR, _view.getSize().y - event.mouseWheelScroll.delta * Define::WORLD_CAMERA_ZOOM_FACTOR);
		}

		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == Controls::WORLD_MAP_MODE_DEFAULT)
			{
				changeMapMode(MapMode::Default);
			}
			if (event.key.code == Controls::WORLD_MAP_MODE_WATER)
			{
				changeMapMode(MapMode::Water);
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

	_data->window.draw(_vertices);

	_data->window.display();
}

void WorldMap::changeMapMode(MapMode mode)
{
	sf::Color baseColor;

	switch (mode)
	{
		case MapMode::Water:
			baseColor = Colors::MAP_MODE_WATER;
			break;
	}

	for (int row = 0; row < Define::WORLD_SIZE; row++)
	{
		for (int column = 0; column < Define::WORLD_SIZE; column++)
		{
			int quadIndex = _tileMatrix[row][column] * 4;

			for (int i = 0; i < 4; i++)
			{
				if (mode == MapMode::Default)
				{
					_vertices[quadIndex + 0].color = sf::Color(sf::Color::Green);
					_vertices[quadIndex + 1].color = sf::Color(sf::Color::Red);
					_vertices[quadIndex + 2].color = sf::Color(sf::Color::Blue);
					_vertices[quadIndex + 3].color = sf::Color(sf::Color::Magenta);
				}
				else
				{
					_vertices[quadIndex + i].color = sf::Color(baseColor) + sf::Color(0, 0, 0, 255 * _tileTerrains.at(mode)[_tileMatrix[row][column]]);
				}
			}
		}
	}
	/*std::cout << "Map Mode: Water\n";
	switch (mode)
	{
		case MapMode::Water:
			for (int row = 0; row < Define::WORLD_SIZE; row++)
			{
				for (int column = 0; column < Define::WORLD_SIZE; column++)
				{
					int quadIndex = _tileMatrix[row][column] * 4;

					_vertices[quadIndex + 0].color = sf::Color(0, 0, 255, 255 * _tiles.water[_tileMatrix[row][column]]);
					_vertices[quadIndex + 1].color = sf::Color(0, 0, 255, 255 * _tiles.water[_tileMatrix[row][column]]);
					_vertices[quadIndex + 2].color = sf::Color(0, 0, 255, 255 * _tiles.water[_tileMatrix[row][column]]);
					_vertices[quadIndex + 3].color = sf::Color(0, 0, 255, 255 * _tiles.water[_tileMatrix[row][column]]);
				}
			}
			break;
	}*/
}