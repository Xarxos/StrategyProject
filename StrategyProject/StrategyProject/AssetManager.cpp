#include "stdafx.h"
#include "AssetManager.h"
#include <SFML\Graphics.hpp>
#include <iostream>

void AssetManager::loadTexture(const std::string &name, const std::string &fileName)
{
	if (!_textures[name].loadFromFile(fileName))
	{
		// TODO: Throw an exception or something.
		std::cout << "Failed to load a texture.\n";
	}
}

sf::Texture& AssetManager::getTexture(const std::string &name)
{
	return _textures.at(name);
}

void AssetManager::loadFont(const std::string &name, const std::string &fileName)
{
	if (!_fonts[name].loadFromFile(fileName))
	{
		// TODO: Throw an exception or something.
		std::cout << "Failed to load a font.\n";
	}
}

sf::Font& AssetManager::getFont(const std::string &name)
{
	return _fonts.at(name);
}

void AssetManager::loadImage(const std::string &name, const std::string &fileName)
{
	if (!_images[name].loadFromFile(fileName))
	{
		// TODO: Throw an exception or something.
		std::cout << "Failed to load an image.\n";
	}
}

sf::Image& AssetManager::getImage(const std::string &name)
{
	return _images.at(name);
}