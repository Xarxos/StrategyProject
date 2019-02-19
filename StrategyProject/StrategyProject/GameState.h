#pragma once

#include "State.h"
#include "Game.h"
#include "SFML\Graphics.hpp"

struct GameData
{
	StateMachine machine;
};

typedef std::shared_ptr<GameData> GameDataRef;

class GameState : public State
{
private:
	EngineDataRef _engine;
	GameDataRef _game = std::make_shared<GameData>();

public:
	GameState(EngineDataRef data) : _engine(data)
	{}

	virtual void init() override;

	virtual void handleInput() override;
	virtual void update(float delta) override;
	virtual void draw() override;
};