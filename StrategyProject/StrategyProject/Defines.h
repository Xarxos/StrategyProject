#pragma once

#include <string>
#include "StateMachine.h"

namespace Define
{
	const int SCREEN_WIDTH(800);
	const int SCREEN_HEIGHT(600);
	const std::string GAME_TITLE("Strategy Game");

	const float SPLASH_STATE_DURATION(3.0f);
}

namespace Filepath
{
	const std::string SPLASH_STATE_BACKGROUND("Resources/Textures/SplashBackground.png");
	const std::string SPLASH_STATE_LOGO("Resources/Textures/SplashLogo.png");

	const std::string MAIN_MENU_BACKGROUND("Resources/Textures/MainMenuBackground.png");
	const std::string TEST_GAME_BUTTON("Resources/Textures/TestGameButton.png");
	const std::string EXIT_GAME_BUTTON("Resources/Textures/ExitButton.png");
}