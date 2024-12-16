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

void Map::drawMap(int view, RenderWindow& window) {
    if (view < CELL_SIZE) {
        view = CELL_SIZE;
    }
    else if (view > (spriteGrid.size() - 1) * CELL_SIZE - window.getSize().x) {
		view = (spriteGrid.size() - 1) * CELL_SIZE - window.getSize().x;
	}
    View mapView(FloatRect(view, 0, window.getSize().x, window.getSize().y));
    window.setView(mapView);
    int cellWidth = CELL_SIZE;
    int visibleStart = view / cellWidth - 1;
    int visibleEnd = (view + window.getSize().x) / cellWidth + 1;

    visibleStart = std::max(1, visibleStart);
    visibleEnd = std::min(static_cast<int>(spriteGrid.size() - 1), visibleEnd);

    cout << visibleStart;

    for (int i = visibleStart; i < visibleEnd; ++i) {
        for (int j = 1; j < spriteGrid[i].size() - 1; ++j) {
            window.draw(*spriteGrid[i][j]);
        }
    }
}

void Map::removeGameObj(vector<GameObject*>& gameObj, GameObject* removeOne) {
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