#include "stdafx.h"
#include "TileDataBoxState.h"
#include "Defines.h"
#include "WorldMap.h"
#include <string>
#include <iostream>

TileDataBoxState::TileDataBoxState(GameDataRef data, const std::map<Terrain, double> &terrainData)
	: _data(data), _terrainData(terrainData)
{
	//_dataText.resize(_terrainData.size());
}

void TileDataBoxState::init()
{
	_data->assets.loadTexture("Tile Data Box", Filepath::TILE_DATA_BOX_BACKGROUND);
	_data->assets.loadFont("Tile Data Box Font", Filepath::TILE_DATA_BOX_FONT);
	_data->assets.loadTexture("Data Box Close Button", Filepath::TILE_DATA_BOX_CLOSE_BUTTON);

	_background.setTexture(_data->assets.getTexture("Tile Data Box"));
	_closeButton.setTexture(_data->assets.getTexture("Data Box Close Button"));

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

		std::cout << "X = " << _background.getPosition().x + _background.getLocalBounds().width / 10 << ", Y = " << _background.getPosition().y + _background.getLocalBounds().height / 6 * loopCount << "\n";
		
		loopCount++;
	}
	
	_closeButton.setPosition(_background.getPosition().x + _background.getLocalBounds().width - _closeButton.getLocalBounds().width, _background.getPosition().y);

	//_logo.setOrigin(sf::Vector2f(_logo.getLocalBounds().width / 2, _logo.getLocalBounds().height / 2));
	//_logo.setPosition(Define::SCREEN_WIDTH / 2, Define::SCREEN_HEIGHT / 2);
}

void TileDataBoxState::handleInput()
{
	sf::Event event;

	while (_data->window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			_data->window.close();
		}

		if (_data->input.isSpriteClicked(_closeButton, sf::Mouse::Left, _data->window))
		{
			_data->machine.removeState();
		}
	}
}

void TileDataBoxState::update(float delta)
{

}

void TileDataBoxState::draw()
{
	//_data->window.clear(sf::Color(sf::Color::White));

	_data->window.draw(_background);
	for (std::map<Terrain, sf::Text>::iterator it = _dataText.begin(); it != _dataText.end(); it++)
	{
		_data->window.draw(it->second);
	}
	_data->window.draw(_closeButton);
	
	//_data->window.display();
}