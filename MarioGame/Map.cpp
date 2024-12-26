#include "Map.h"
#include "Global.h"
#include <iostream>

// Cell Implementation
Cell::Cell() : x(-1), y(-1), type(0) {}

Cell::Cell(int x, int y, int type) {
    this->x = x;
    this->y = y;
    this->type = type;
}

int Cell::getX() const{
    return x;
}

int Cell::getY() const{
    return y;
}

int Cell::getType() const{
    return type;
}

// Map Implementation
Map::Map() : textures(50) {
    cellProperties = {};
    colorToType = {};
}

Map::Map(const std::map<int, CellProperties>& cellProps,
    const std::map<sf::Color, int, ColorComparator>& colorMap) 
    : cellProperties(cellProps),
    colorToType(colorMap.begin(), colorMap.end(), ColorComparator()), // Explicitly construct with comparator
    textures(50) {}

bool Map::isBreakable(const Cell& cell) const {
    int type = cell.getType();
    auto it = cellProperties.find(type);

    if (it != cellProperties.end()) {
        return it->second.breakable;
    }

    return false;
}

bool Map::isCollectable(const Cell& cell) const {
	int type = cell.getType();
	auto it = cellProperties.find(type);

    if (it != cellProperties.end()) {
		return it->second.collectable;
	}

	return false;
}

vector<vector<Cell>>& Map::getMap() {
    return cellGrid;
}

vector<vector<Sprite*>>& Map::getSpriteGrid() {
	return spriteGrid;
}

void Map::setMap(vector<vector<Cell>> map) {
    this->cellGrid = map;
}

void Map::addCell(Cell cell) {
    if (cell.getX() >= 0 && cell.getX() < cellGrid.size() &&
        cell.getY() >= 0 && cell.getY() < cellGrid[0].size()) {
        cellGrid[cell.getX()][cell.getY()] = cell;
    }
}

void Map::clearMap() {
    for (int i = 0; i < cellGrid.size(); i++) {
        for (int j = 0; j < cellGrid[i].size(); j++) {
            cellGrid[i][j] = Cell(i, j, 0);
        }
    }
}

bool Map::loadTexture(string texture_file_name, int type) {
    if (type < 0 || type >= textures.size()) {
        cerr << "Invalid type: " << type << endl;
        return false;
    }

    Texture texture;
    if (!texture.loadFromFile(texture_file_name)) {
        cerr << "Error loading " << texture_file_name << endl;
        return false;
    }
    textures[type] = texture;
    return true;
}

void Map::drawMap(const Sprite& character, RenderWindow& window) {
    int view_x = character.getGlobalBounds().left - WIDTH/2;
    if (view_x < CELL_SIZE) {
        view_x = CELL_SIZE;
    }
    else if (view_x > (spriteGrid.size() - 1) * CELL_SIZE - window.getSize().x) {
		view_x = (spriteGrid.size() - 1) * CELL_SIZE - window.getSize().x;
	}

    int veiw_y = character.getGlobalBounds().top - HEIGHT / 2;
    if (veiw_y < CELL_SIZE) {
		veiw_y = CELL_SIZE;
	}
    else if (veiw_y > (spriteGrid[0].size() - 1) * CELL_SIZE - window.getSize().y) {
		veiw_y = (spriteGrid[0].size() - 1) * CELL_SIZE - window.getSize().y;
	}

    View mapView(FloatRect(view_x, veiw_y, window.getSize().x, window.getSize().y));
    window.setView(mapView);

    int cellWidth = CELL_SIZE;
    int visibleStart_x = view_x / cellWidth - 1;
    int visibleEnd_x = (view_x + window.getSize().x) / cellWidth + 1;

    visibleStart_x = std::max(1, visibleStart_x);
    visibleEnd_x = std::min(static_cast<int>(spriteGrid.size() - 1), visibleEnd_x);

    int cellHeight = CELL_SIZE;
    int visibleStart_y = veiw_y / cellHeight - 1;
    int visibleEnd_y = (veiw_y + window.getSize().y) / cellHeight + 1;

    visibleStart_y = std::max(1, visibleStart_y);
    visibleEnd_y = std::min(static_cast<int>(spriteGrid[0].size() - 1), visibleEnd_y);

    for (int i = visibleStart_x; i < visibleEnd_x; ++i) {
        for (int j = visibleStart_y - 1; j < visibleEnd_y; ++j) {
            window.draw(*spriteGrid[i][j]);
        }
    }
}

void Map::removeGameObj(vector<GameObject*>& gameObj, GameObject* removeOne) {
    if (std::find(gameObj.begin(), gameObj.end(), removeOne) == gameObj.end()) {
        cout << "Object not found" << endl;
        return;
    }

    int x_coord = static_cast<int>(removeOne->m_sprite.getPosition().x / CELL_SIZE);
    int y_coord = static_cast<int>(removeOne->m_sprite.getPosition().y / CELL_SIZE);
    if (x_coord >= 0 && x_coord < cellGrid.size() &&
        y_coord >= 0 && y_coord < cellGrid[0].size()) {
		cellGrid[x_coord][y_coord] = Cell(x_coord, y_coord, 0);
        spriteGrid[x_coord][y_coord] = new Sprite(textures[0]);
        spriteGrid[x_coord][y_coord]->setPosition(x_coord * CELL_SIZE, y_coord * CELL_SIZE);
        spriteGrid[x_coord][y_coord]->setScale(SCALE, SCALE);
	}
	gameObj.erase(std::remove(gameObj.begin(), gameObj.end(), removeOne), gameObj.end());
    cout << "Removed cell at " << x_coord << " " << y_coord << endl;
}

void Map::removeGameObj(vector<vector<GameObject*>>& objMap,vector<GameObject*>& brick, vector<GameObject*>& luckyBlock, vector<GameObject*>& coin, int x, int y) {
    if (x >= 0 && x < cellGrid.size() &&
        y >= 0 && y < cellGrid[0].size() && objMap[x][y] != nullptr) {

        
        if (cellGrid[x][y].getType() == 1) {
            brick.erase(std::remove(brick.begin(), brick.end(), objMap[x][y]), brick.end());
        }
        else if (cellGrid[x][y].getType() == 2) {
            luckyBlock.erase(std::remove(luckyBlock.begin(), luckyBlock.end(), objMap[x][y]), luckyBlock.end());
        }
        else if (cellGrid[x][y].getType() == 3) {
            coin.erase(std::remove(coin.begin(), coin.end(), objMap[x][y]), coin.end());
        }
        cellGrid[x][y] = Cell(x, y, 0);
        spriteGrid[x][y] = new Sprite(textures[0]);
        spriteGrid[x][y]->setPosition(x * CELL_SIZE, y * CELL_SIZE);
        spriteGrid[x][y]->setScale(SCALE, SCALE);
        objMap[x][y] = nullptr;
        std::cout << "Type: " << cellGrid[x][y].getType() << std::endl;
        std::cout << "Brick size: " << brick.size() << std::endl;
        std::cout << "Coin size: " << coin.size() << std::endl;
        cout << "Removed cell at " << x << " " << y << endl;
	}
}

void Map::removeGameObj(vector<vector<GameObject*>>& objMap, vector<GameObject*>& brick, vector<GameObject*>& luckyBlock, vector<GameObject*>& coin, GameObject* obj) {
	int x = round((obj->m_sprite.getGlobalBounds().left / CELL_SIZE));
	int y = round((obj->m_sprite.getGlobalBounds().top / CELL_SIZE));
	removeGameObj(objMap, brick, luckyBlock, coin, x, y);
}

#include "Items.h"
#include "Mushroom.h"
#include "LuckyBlock.h"

void Map::spawnMushroom(vector<vector<GameObject*>>& objMap,vector<GameObject*> items, GameObject* luckyblock) {
    if (!static_cast<LuckyBlock*>(luckyblock)->doesItContainMushroom()) {
        cout << "Unlucky block" << endl;
        return;
    }
    int x = round((luckyblock->m_sprite.getGlobalBounds().left / CELL_SIZE));
    int y = round((luckyblock->m_sprite.getGlobalBounds().top / CELL_SIZE)) - 1;
    Items* item = new Mushroom("./Resources/Item/mushroom.png", "false");
    item->m_name = "Mushroom";
    item->m_sprite.setPosition(x * CELL_SIZE, y * CELL_SIZE);
    item->m_sprite.setScale(SCALE, SCALE);
    spriteGrid[x][y] = &item->m_sprite;
    items.push_back(item);
    objMap[x][y] = item;
}