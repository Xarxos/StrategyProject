#pragma once

#include <memory>
#include <string>
#include <SFML\Graphics.hpp>
#include "StateMachine.h"
#include "AssetManager.h"
#include "InputManager.h"

struct EngineData
{
	StateMachine machine;
	sf::RenderWindow window;
	AssetManager assets;
	InputManager input;
};

typedef std::shared_ptr<EngineData> EngineDataRef;

class Game
{
private:
	sf::Clock _clock;
	EngineDataRef _engine = std::make_shared<EngineData>();

public:
	Game(int windowWidth, int windowHeight, std::string title);

private:
	void run();
};