#pragma once
#include "Items.h"
class Coins : public Items
{
public:
	const std::string path = "";
	int status = 0;
public:
	Coins() {}

	Coins(std::string path, std::string path1, std::string isBreakable) {
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

	void update(float deltaTime) override {
		std::cout << "Update coins" << std::endl;
		m_elapsedTime += deltaTime;
		if (m_elapsedTime >= 0.3f) {
			m_elapsedTime = 0.f;

			if (status == 0) {
				m_sprite.setTexture(m_textureAfter);

			}
			else
				m_sprite.setTexture(m_texture);

			status = 1 - status;
		}
	}

	void special() override {}
};

