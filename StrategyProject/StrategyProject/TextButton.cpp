#include "stdafx.h"
#include "TextButton.h"
#include "SFML\Graphics.hpp"

TextButton::TextButton()
{
	//setTextSize(Config::SQUARE_SIZE * 2);
	_text.setStyle(sf::Style::Default);

	_text.setFillColor(sf::Color::Black);
	_background.setColor(sf::Color::White);
}

TextButton::TextButton(const sf::String &string, const sf::Font &font, int textSize, sf::Uint32 style)
{
	_text.setFont(font);
	setString(string);
	setTextSize(textSize);
	_text.setStyle(style);

	_text.setFillColor(sf::Color::Black);
	_background.setColor(sf::Color::White);
}

void TextButton::setPosition(float x, float y)
{
	_text.setPosition(x, y);
	_background.setPosition(x, y);
}

void TextButton::setOrigin(const sf::Vector2f &origin)
{
	_text.setOrigin(origin.x * (1 / 1.1f), origin.y * 1.8f);
	_background.setOrigin(origin);
}

void TextButton::setScale(const sf::Vector2f &factors)
{
	_text.setScale(factors);
	_background.setScale(sf::Vector2f(_text.getGlobalBounds().width * 1.1f, _text.getGlobalBounds().height * 1.1f));
}

void TextButton::setTextSize(int size)
{
	_text.setCharacterSize(size);
	_background.setScale(sf::Vector2f(_text.getGlobalBounds().width * 1.1f, _text.getGlobalBounds().height * 1.1f));
}

void TextButton::setString(const sf::String &string)
{
	_text.setString(string);
	_background.setScale(sf::Vector2f(_text.getGlobalBounds().width * 1.1f, _text.getGlobalBounds().height * 1.1f));
}

void TextButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_background, states);
	target.draw(_text, states);
}