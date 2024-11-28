#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
class GameObject
{
public:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	std::string m_isBreakable;
	std::string m_path;
public:
	GameObject() {};

	GameObject(std::string path) {
		if (!m_texture.loadFromFile(path)) {
			std::cerr << "Can not load Resources \n";
			return;
		}

		m_sprite.setTexture(m_texture);
	}

	void load(std::string path) {
		if (!m_texture.loadFromFile(path)) {
			std::cerr << "Can not load Resources \n";
			return;
		}
		m_sprite.setTexture(m_texture);
	}

	void draw(sf::RenderWindow& window, float x, float y) {
		m_sprite.setPosition(x, y);
		window.draw(m_sprite);
	}

	sf::FloatRect getBounds() {
		return m_sprite.getLocalBounds(); // ?? Does it correct
	}

	virtual ~GameObject() = default;
};

