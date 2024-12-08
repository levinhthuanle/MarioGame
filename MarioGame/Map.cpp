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

vector<vector<Sprite>>& Map::getSpriteGrid() {
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

void Map::removeCell(int x, int y) {
    if (x >= 0 && x < cellGrid.size() && y >= 0 && y < cellGrid[0].size()) {
        cellGrid[x][y] = Cell(x, y, 0);
    }
}

void Map::clearMap() {
    for (int i = 0; i < cellGrid.size(); i++) {
        for (int j = 0; j < cellGrid[i].size(); j++) {
            cellGrid[i][j] = Cell(i, j, 0);
        }
    }
}

bool Map::readSketch(string sketch_file_name) {
    sf::Image sketch;
    if (!sketch.loadFromFile(sketch_file_name)) {
        cerr << "Error loading " << sketch_file_name << endl;
        return false;
    }

    int width = sketch.getSize().x;
    int height = sketch.getSize().y;

    cellGrid = vector<vector<Cell>>(width, vector<Cell>(height, Cell()));
    spriteGrid = vector<vector<Sprite>>(width, vector<Sprite>(height, Sprite()));

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            sf::Color color = sketch.getPixel(x, y);
            auto it = colorToType.find(color);
            int type = (it != colorToType.end()) ? it->second : 0;
            cellGrid[x][y] = Cell(x, y, type);
            Sprite cell;
            cell.setTexture(textures[type]);
            cell.setScale(SCALE, SCALE);
            cell.setPosition((x * CELL_SIZE), (y * CELL_SIZE));
            spriteGrid[x][y] = cell;
        }
    }
    return true;
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
    View mapView(FloatRect(view, 0, window.getSize().x, window.getSize().y));
    window.setView(mapView);

    int cellWidth = CELL_SIZE;
    int visibleStart = view / cellWidth;
    int visibleEnd = (view + window.getSize().x) / cellWidth;

    visibleStart = std::max(0, visibleStart);
    visibleEnd = std::min(static_cast<int>(spriteGrid.size()), visibleEnd);

    for (int i = visibleStart; i < visibleEnd; ++i) {
        for (int j = 0; j < spriteGrid[i].size(); ++j) {
            window.draw(spriteGrid[i][j]);
        }
    }
}