#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
class Button {
public:
	sf::Texture texture;
	sf::Sprite sprite;
	int m_x = 0;
	int m_y = 0;

	Button() {}

	Button(std::string path) {
		if (!texture.loadFromFile(path)) {
			std::cerr << "Can not load button Texture \n";
			return;
		}

		sprite.setTexture(texture);
	}

	Button(std::string path, int x, int y) {
		if (!texture.loadFromFile(path)) {
			std::cerr << "Can not load button Texture \n";
			return;
		}


		sprite.setTexture(texture);
		sprite.setPosition(x, y);
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

	void draw(sf::RenderWindow& window) {
		window.draw(sprite);
	}
};

class TextRemake {
private:
	sf::Text m_text;
public:
	sf::Font font;
	std::string path = "./Resources/fonts/arial.ttf";

	TextRemake(std::string& text) {
		if (!font.loadFromFile(path)) {
			std::cerr << "Error loading font\n";
		}
		m_text.setFont(font);
		m_text.setString(text);
		m_text.setCharacterSize(25);
		m_text.setFillColor(sf::Color::Black);
		m_text.setPosition(0, 0);
	}

	TextRemake() {
		if (!font.loadFromFile(path)) {
			std::cerr << "Error loading font\n";
		}
		m_text.setFont(font);
		m_text.setString("");
		m_text.setCharacterSize(25);
		m_text.setFillColor(sf::Color::Black);
		m_text.setPosition(0, 0);
	}

	TextRemake(const std::string& text, unsigned int size, float x, float y) {

		if (!font.loadFromFile(path)) {
			std::cerr << "Error loading font\n";
		}
		m_text.setFont(font);
		m_text.setString(text);
		m_text.setCharacterSize(size);
		m_text.setFillColor(sf::Color::Black);
		m_text.setPosition(x, y);
	}

	// Setters
	void setText(const std::string& text) {
		m_text.setString(text);
	}

	void setFont(const sf::Font& font) {
		m_text.setFont(font);
	}

	void setCharacterSize(unsigned int size) {
		m_text.setCharacterSize(size);
	}

	void setFillColor(const sf::Color& color) {
		m_text.setFillColor(color);
	}

	void setPosition(float x, float y) {
		m_text.setPosition(x, y);
	}

	// Getters
	std::string getText() const {
		return m_text.getString();
	}

	sf::Font getFont() const {
		return *m_text.getFont();
	}

	unsigned int getCharacterSize() const {
		return m_text.getCharacterSize();
	}

	sf::Color getFillColor() const {
		return m_text.getFillColor();
	}

	sf::Vector2f getPosition() const {
		return m_text.getPosition();
	}

	// Draw method
	void draw(sf::RenderWindow& window) const {
		window.draw(m_text);
	}


};