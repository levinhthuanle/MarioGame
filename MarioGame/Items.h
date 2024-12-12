#pragma once
#include "GameObject.h"
class Items : public GameObject
{
public:
	Items() {}

	Items(std::string path, std::string isBreakable) {
		this->m_path = path;
		this->m_isBreakable = isBreakable;

		if (!m_texture.loadFromFile(path)) {
			std::cerr << "Can not load Resources \n";
			return;
		}

		m_sprite.setTexture(m_texture);
	}

	Items(std::string path, std::string path1, std::string isBreakable) {
		this->m_path = path;
		this->m_isBreakable = isBreakable;

		if (!m_texture.loadFromFile(path)) {
			std::cerr << "Can not load Resources \n";
			return;
		}

		if (!m_textureAfter.loadFromFile(path1)) {
			std::cerr << "Can not load Resources \n";
			return;
		}

		m_sprite.setTexture(m_texture);
	}

	virtual void update(float deltaTime) {
		std::cout << "Items updated!" << std::endl;
	}

	virtual void special() {}
};

