#include "stdafx.h"
#include "SubState.h"
#include "Box.h"
#include "SFML\Graphics.hpp"
#include "RegionDataBox.h"

#include <set>

RegionDataBox::RegionDataBox(EngineDataRef engineData, DatabaseRef database, int regionIndex, sf::Vector2i regionCoords)
	: Box(engineData, database, { "Overview", "Bedrock" }),
	_regionIndex(regionIndex),
	_regionCoords(regionCoords)
{

}

void RegionDataBox::init()
{
	Box::init();

	_engine->assets.loadTexture("Tile Data Box Enter Button", Filepath::TILE_DATA_BOX_ENTER_BUTTON);

	_enterButton.setTexture(_engine->assets.getTexture("Tile Data Box Enter Button"));

	_enterButton.setPosition(_background.getPosition().x + _background.getLocalBounds().width - _enterButton.getLocalBounds().width, _background.getPosition().y + _background.getLocalBounds().height - _enterButton.getLocalBounds().height);

	initRegionData();
}

void RegionDataBox::initRegionData()
{
	sf::String bedrockMainStoneTypesHeadlineStr = "Main Stone Types In This Region";
	sf::Text bedrockMainStoneTypesHeadline;
	bedrockMainStoneTypesHeadline.setString(bedrockMainStoneTypesHeadlineStr);
	bedrockMainStoneTypesHeadline.setStyle(Graphics::BOX_HEADLINE_TEXT_STYLE);
	bedrockMainStoneTypesHeadline.setFont(_engine->assets.getFont("Box Tab Font"));
	bedrockMainStoneTypesHeadline.setCharacterSize(Graphics::BOX_HEADLINE_TEXT_SIZE);
	bedrockMainStoneTypesHeadline.setFillColor(Colors::BOX_TEXT);

	_tabs.at("Bedrock").addText(bedrockMainStoneTypesHeadline);
	_tabs.at("Bedrock").setTextRelativePosition(0, 10.f, 0.f);

	std::set<int> mainStoneTypeIndexes;

	for (const auto &tile : _database->regions.at(_regionIndex).tiles)
	{
		mainStoneTypeIndexes.insert(tile.bedrock.mainStoneTypeIndex);
	}

	int loopCount(0);

	for (const auto &mainStoneTypeIndex : mainStoneTypeIndexes)
	{
		sf::String mainStoneTypeName = _database->stoneTypes.at(mainStoneTypeIndex)->name;
		sf::Text mainStoneType;
		mainStoneType.setString(mainStoneTypeName);
		mainStoneType.setFont(_engine->assets.getFont("Box Tab Font"));
		mainStoneType.setCharacterSize(Graphics::BOX_TEXT_SIZE);
		mainStoneType.setFillColor(Colors::BOX_TEXT);

		_tabs.at("Bedrock").addText(mainStoneType);
		_tabs.at("Bedrock").setTextRelativePosition(loopCount + 1, 10.f, Graphics::BOX_HEADLINE_TEXT_SIZE + Graphics::BOX_TEXT_SIZE * loopCount);
		loopCount++;
	}
}

bool RegionDataBox::handleInput(sf::Event &event)
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
void RegionDataBox::update(float delta)
{
	if (_boxPressed)
	{
		sf::Vector2i currentMousePos = _engine->input.getMousePosition(_engine->window);
		sf::Vector2i deltaMousePos = currentMousePos - _previousMousePos;

		_enterButton.move(deltaMousePos.x, deltaMousePos.y);
	}

	Box::update(delta);
}
void RegionDataBox::draw()
{
	Box::draw();

	_engine->window.draw(_enterButton);
}