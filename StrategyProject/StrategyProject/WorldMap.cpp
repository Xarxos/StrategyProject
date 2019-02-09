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

}

void WorldMap::init()
{
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
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		std::cout << "W";
		//cout << "View.getCenter().y - View.getSize().y / 2: " << view.getCenter().y - view.getSize().y / 2 << " | map.getGlobalBounds.().height: " << map.getGlobalBounds().height << "\n";
		if (_view.getCenter().y - _view.getSize().y / 2 > 0)
		{
			_view.move(0.f, -5.f);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		std::cout << "S";
		if (_view.getCenter().y + _view.getSize().y / 2 < Define::WORLD_SIZE * Define::TILE_SIZE)
		{
			_view.move(0.f, 5.f);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		std::cout << "A";
		if (_view.getCenter().x - _view.getSize().x / 2 > 0)
		{
			_view.move(-5.f, 0.f);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		std::cout << "D";
		if (_view.getCenter().x + _view.getSize().x / 2 < Define::WORLD_SIZE * Define::TILE_SIZE)
		{
			_view.move(5.f, 0.f);
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