#pragma once

#include "SFML\Graphics.hpp"

class TextButton : public sf::Drawable
{
private:
	sf::Text _text;
	sf::Sprite _background;

public:
	TextButton();
	TextButton(const sf::String &string, const sf::Font &font, int textSize, sf::Uint32 style = sf::Style::Default);

	virtual sf::FloatRect getBounds() { return _background.getGlobalBounds(); }

	void setFont(const sf::Font &font) { _text.setFont(font); }
	void setStyle(sf::Uint32 style) { _text.setStyle(style); }
	void setTextColor(const sf::Color &textColor) { _text.setFillColor(textColor); }
	void setButtonColor(const sf::Color &buttonColor) { _background.setColor(buttonColor); }

	//const sf::Vector2f& getButtonSize() const { return _background.getSize(); }

	void setPosition(float x, float y);
	void setOrigin(const sf::Vector2f &origin);
	void setScale(const sf::Vector2f &factors);
	void setTextSize(int size);
	void setString(const sf::String &string);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
