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

	virtual void special() {}
};

