// StrategyProject.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Defines.h"
#include "Game.h"
#include "SplashState.h"

int main()
{
	srand(static_cast<unsigned int>(time(0)));
	rand();

	Game(Define::SCREEN_WIDTH, Define::SCREEN_HEIGHT, Define::GAME_TITLE);

    return 0;
}

