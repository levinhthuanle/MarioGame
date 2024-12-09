#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
class Button {
public:
	sf::Texture texture;
	sf::Sprite sprite;

	Button() {}

	Button(std::string path) {
		if (!texture.loadFromFile(path)) {
			std::cerr << "Can not load button Texture \n";
			return;
		}

		sprite.setTexture(texture);
	}

	bool isClicked(const sf::RenderWindow& window, sf::Event event) {
		if (event.type == sf::Event::MouseButtonPressed) {
			if (event.mouseButton.button == sf::Mouse::Left) {
				sf::Vector2i mousePos = sf::Mouse::getPosition(window);
				if (sprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
					return true;
				}
			}
		}
		return false;
	}
	bool isHover(const sf::RenderWindow& window) {
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		if (sprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
			return true;
		}
		return false;
	}

	void loadButton(std::string path) {
		if (!texture.loadFromFile(path)) {
			std::cerr << "Can not load button Texture \n";
			return;
		}

		sprite.setTexture(texture);
	}

	void setOpacity(int value) {
		sf::Color spriteColor = sprite.getColor();
		spriteColor.a = value;
		sprite.setColor(spriteColor);
	}

	void draw(sf::RenderWindow& window, float x, float y) {
		sprite.setPosition(x, y);
		window.draw(sprite);
	}
};

class Text {

};