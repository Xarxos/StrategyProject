#include "stdafx.h"
#include "TileDataBoxState.h"
#include "Defines.h"
#include "WorldMap.h"
#include <string>
#include <iostream>

TileDataBoxState::TileDataBoxState(GameDataRef data, sf::Vector2i tileCoords, const std::map<Terrain, double> &terrainData)
	: _data(data),
	_tileCoords(tileCoords),
	_terrainData(terrainData),
	_view(sf::Vector2f(Define::WORLD_VIEW_WIDTH / 2, Define::WORLD_VIEW_HEIGHT / 2), sf::Vector2f(Define::WORLD_VIEW_WIDTH, Define::WORLD_VIEW_HEIGHT)),
	_mouseButtonHeld(false)
{

}

void TileDataBoxState::init()
{
	_data->assets.loadTexture("Tile Data Box", Filepath::TILE_DATA_BOX_BACKGROUND);
	_data->assets.loadTexture("Tile Data Box Selected", Filepath::TILE_DATA_BOX_SELECTED);
	_data->assets.loadTexture("Tile Data Box Close Button", Filepath::TILE_DATA_BOX_CLOSE_BUTTON);
	_data->assets.loadFont("Tile Data Box Font", Filepath::TILE_DATA_BOX_FONT);

	_background.setTexture(_data->assets.getTexture("Tile Data Box"));
	_closeButton.setTexture(_data->assets.getTexture("Tile Data Box Close Button"));

	int loopCount(1);

	for (std::map<Terrain, double>::iterator it = _terrainData.begin(); it != _terrainData.end(); it++)
	{
		std::string dataString;

		switch (it->first)
		{
			case Terrain::Water:
				dataString = "Water: ";
				break;

			case Terrain::FlatGround:
				dataString = "Flat Ground: ";
				break;

			case Terrain::Hills:
				dataString = "Hills: ";
				break;

			case Terrain::Mountains:
				dataString = "Mountains: ";
				break;

			case Terrain::Forest:
				dataString = "Forest: ";
				break;
		}

		int asPercentage = std::round(it->second * 100);
		dataString.append(std::to_string(asPercentage));
		dataString.append("%");

		_dataText[it->first].setString(dataString);
		_dataText[it->first].setFont(_data->assets.getFont("Tile Data Box Font"));
		_dataText[it->first].setCharacterSize(24);
		_dataText[it->first].setFillColor(sf::Color::Black);
		_dataText[it->first].setPosition(_background.getPosition().x + _background.getLocalBounds().width / 10, _background.getPosition().y + _background.getLocalBounds().height / 6 * loopCount);
		
		_closeButton.setPosition(_background.getPosition().x + _background.getLocalBounds().width - _closeButton.getLocalBounds().width, _background.getPosition().y);

		loopCount++;
	}
}

bool TileDataBoxState::handleInput(sf::Event &event)
{
	if (event.type == sf::Event::Closed)
	{
		_data->window.close();
		return true;
	}

	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (_data->input.isSpriteClicked(_closeButton, sf::Mouse::Left, _data->window))
		{
			_remove = true;
			return true;
		}
	}

	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (_data->input.isSpriteClicked(_background, sf::Mouse::Left, _data->window))
		{
			_moveToTop = true;
			_mouseButtonHeld = true;
			_previousMousePos = _data->input.getMousePosition(_data->window);

			return true;
		}
	}

	if (event.type == sf::Event::MouseButtonReleased)
	{
		if (_mouseButtonHeld)
		{
			_mouseButtonHeld = false;

			return true;
		}
	}

	return false;
}

void TileDataBoxState::update(float delta)
{
	if (_mouseButtonHeld)
	{
		sf::Vector2i currentMousePos = _data->input.getMousePosition(_data->window);
		sf::Vector2i deltaMousePos = currentMousePos - _previousMousePos;

		_background.setPosition(_background.getPosition().x + deltaMousePos.x, _background.getPosition().y + deltaMousePos.y);
		_closeButton.setPosition(_closeButton.getPosition().x + deltaMousePos.x, _closeButton.getPosition().y + deltaMousePos.y);

		for (std::map<Terrain, sf::Text>::iterator it = _dataText.begin(); it != _dataText.end(); it++)
		{
			it->second.setPosition(it->second.getPosition().x + deltaMousePos.x, it->second.getPosition().y + deltaMousePos.y);
		}

		_previousMousePos = currentMousePos;
	}

	if (_moveToTop)
	{
		_moveToTop = false;
	}
}

void TileDataBoxState::draw()
{
	_data->window.setView(_view);

	_data->window.draw(_background);
	for (std::map<Terrain, sf::Text>::iterator it = _dataText.begin(); it != _dataText.end(); it++)
	{
		_data->window.draw(it->second);
	}
	_data->window.draw(_closeButton);
}

void TileDataBoxState::selectBox(bool isSelected)
{
	if (isSelected)
	{
		_background.setTexture(_data->assets.getTexture("Tile Data Box Selected"));
	}
	else
	{
		_background.setTexture(_data->assets.getTexture("Tile Data Box"));
	}
}