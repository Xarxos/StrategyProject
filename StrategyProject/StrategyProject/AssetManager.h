#pragma once

#include <map>

#include <SFML\Graphics.hpp>

class AssetManager
{
private:
	std::map<std::string, sf::Texture> _textures;
	std::map<std::string, sf::Font> _fonts;
	std::map<std::string, sf::Image> _images;

public:
	AssetManager() {}
	~AssetManager() {}

	void loadTexture(const std::string &name, const std::string &fileName);
	sf::Texture& getTexture(const std::string &name);

	void loadFont(const std::string &name, const std::string &fileName);
	sf::Font& getFont(const std::string &name);

	void loadImage(const std::string &name, const std::string &fileName);
	sf::Image& getImage(const std::string &name);
};
