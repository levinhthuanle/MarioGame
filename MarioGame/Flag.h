#pragma once
#include "GameObject.h"
class Flag : public GameObject {
public:
	Flag() {
		if (!m_texture.loadFromFile(FLAG_PATH)) {
			std::cerr << "Can not load flag Texture \n";
			return;
		}
		m_sprite.setTexture(m_texture);
	}
	const std::string FLAG_PATH = ".Resources/Item/flag.png";

	bool isWin = false;
};
