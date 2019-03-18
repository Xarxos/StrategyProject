#include "stdafx.h"
#include "SubState.h"
#include "Box.h"
#include "SFML\Graphics.hpp"
#include "TileDataBox.h"

TileDataBox::TileDataBox(EngineDataRef engineData, DatabaseRef database, int tileIndex, sf::Vector2i tileCoords)
	: Box(engineData, database, { "Overview", "Bedrock" }),
	_tileIndex(tileIndex),
	_tileCoords(tileCoords)
{

}

void TileDataBox::init()
{
	Box::init();

	_engine->assets.loadTexture("Tile Data Box Enter Button", Filepath::TILE_DATA_BOX_ENTER_BUTTON);

	_enterButton.setTexture(_engine->assets.getTexture("Tile Data Box Enter Button"));

	_enterButton.setPosition(_background.getPosition().x + _background.getLocalBounds().width - _enterButton.getLocalBounds().width, _background.getPosition().y + _background.getLocalBounds().height - _enterButton.getLocalBounds().height);

	initTileData();
}

void TileDataBox::initTileData()
{
	sf::Text bedrockMainStoneType;
	bedrockMainStoneType.setString("Zagite");
	bedrockMainStoneType.setFont(_engine->assets.getFont("Box Tab Font"));
	bedrockMainStoneType.setCharacterSize(Graphics::BOX_TEXT_SIZE);
	bedrockMainStoneType.setFillColor(Colors::BOX_TEXT);

	_tabs.at("Bedrock").addText(bedrockMainStoneType);
	_tabs.at("Bedrock").setTextLocalPosition(0, 50.f, 50.f);
}

bool TileDataBox::handleInput(sf::Event &event)
{
	if (Box::handleInput(event))
	{
		return true;
	}

	if (_engine->input.isSpriteClicked(_enterButton, sf::Mouse::Left, _engine->window))
	{
		//_engine->machine.addState(stateRef(new RegionMap(_engine, _database)), false);
		return true;
	}

	return false;
}
void TileDataBox::update(float delta)
{
	if (_mouseButtonHeld)
	{
		sf::Vector2i currentMousePos = _engine->input.getMousePosition(_engine->window);
		sf::Vector2i deltaMousePos = currentMousePos - _previousMousePos;

		_enterButton.setPosition(_enterButton.getPosition().x + deltaMousePos.x, _enterButton.getPosition().y + deltaMousePos.y);
	}

	Box::update(delta);
}
void TileDataBox::draw()
{
	Box::draw();

	_engine->window.draw(_enterButton);
}