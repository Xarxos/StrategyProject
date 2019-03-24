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
	_tabs.at("Bedrock").setTextRelativePosition(0, 50.f, 50.f);

	sf::Text testText1;
	testText1.setString("Baby Doll");
	testText1.setFont(_engine->assets.getFont("Box Tab Font"));
	testText1.setCharacterSize(Graphics::BOX_TEXT_SIZE);
	testText1.setFillColor(Colors::BOX_TEXT);

	_tabs.at("Bedrock").addText(testText1);
	_tabs.at("Bedrock").setTextRelativePosition(1, 50.f, 250.f);

	sf::Text testText2;
	testText1.setString("Baby Doller");
	testText1.setFont(_engine->assets.getFont("Box Tab Font"));
	testText1.setCharacterSize(Graphics::BOX_TEXT_SIZE);
	testText1.setFillColor(Colors::BOX_TEXT);

	_tabs.at("Overview").addText(testText1);
	_tabs.at("Overview").setTextRelativePosition(0, 5.f, 10.f);

	sf::Text testText3;
	testText1.setString("Mainstay");
	testText1.setFont(_engine->assets.getFont("Box Tab Font"));
	testText1.setCharacterSize(Graphics::BOX_TEXT_SIZE);
	testText1.setFillColor(Colors::BOX_TEXT);

	_tabs.at("Overview").addText(testText1);
	_tabs.at("Overview").setTextRelativePosition(1, 25.f, 35.f);
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
	if (_boxPressed)
	{
		sf::Vector2i currentMousePos = _engine->input.getMousePosition(_engine->window);
		sf::Vector2i deltaMousePos = currentMousePos - _previousMousePos;

		_enterButton.move(deltaMousePos.x, deltaMousePos.y);
	}

	Box::update(delta);
}
void TileDataBox::draw()
{
	Box::draw();

	_engine->window.draw(_enterButton);
}