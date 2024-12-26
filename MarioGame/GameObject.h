#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include <string>

using namespace std;

class GameObject
{
public:
	string m_name;
	float m_elapsedTime = 0.f;
	sf::Texture m_texture;
	sf::Texture m_textureAfter;
	sf::Sprite m_sprite;
	std::string m_isBreakable;
	std::string m_path;
	sf::Vector2f position;
public:
	GameObject() {};

	GameObject(std::string path) {
		if (!m_texture.loadFromFile(path)) {
			std::cerr << "Can not load Resources \n";
			return;
		}
		m_sprite.setTexture(m_texture);
	}

	GameObject(std::string path, std::string pathAfter, std::string name) {
		if (!m_textureAfter.loadFromFile(pathAfter)) {
			std::cerr << "Can not load Resources \n";
			return;
		}

		if (!m_texture.loadFromFile(path)) {
			std::cerr << "Can not load Resources \n";
			return;
		}
		m_sprite.setTexture(m_texture);
		m_name = name;
	}

	GameObject(std::string path, std::string name) {
		if (!m_texture.loadFromFile(path)) {
			std::cerr << "Can not load Resources \n";
			return;
		}
		m_sprite.setTexture(m_texture);
		m_name = name;
	}

	virtual void update(float deltaTime) {
		std::cout << "Update game objects \n";
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

	void draw(sf::RenderWindow& window) {
		window.draw(m_sprite);
	}

	virtual void tryBreak() {
		m_sprite.setTexture(m_textureAfter);
	}

	sf::FloatRect getBounds() {
		return m_sprite.getGlobalBounds(); // ?? Does it correct
	}

	virtual ~GameObject() = default;
};

