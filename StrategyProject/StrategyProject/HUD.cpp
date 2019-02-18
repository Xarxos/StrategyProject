#include "stdafx.h"
#include "Defines.h"
#include "HUD.h"
#include "SFML\Graphics.hpp"

void Hud::init()
{
	_engine->assets.loadTexture("HUD Background", Filepath::HUD_BACKGROUND);

	_background.setTexture(_engine->assets.getTexture("HUD Background"));
}

void Hud::draw()
{
	_engine->window.setView(_view);

	_engine->window.draw(_background);
}