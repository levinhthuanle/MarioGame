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
    // Initialize default cell properties
    cellProperties = {
        {1, {true, false}},  // Brick
        {2, {false, true}},  // Lucky Block
        {3, {false, false}}, // Grass
        {4, {false, false}}, // Dirt
        {5, {false, false}}, // Pipe Top Left
        {6, {false, false}}, // Pipe Top Right
        {7, {false, false}}, // Pipe Body Left
        {8, {false, false}}, // Pipe Body Right
        {9, {false, false}}, // Steel
        {10, {false, false}}, // Flag Body
        {11, {false, false}}  // Flag Top
    };

    // Initialize color-to-type mapping
    colorToType = {
        {Color(254, 138, 24), 1},  // Brick
        {Color(255, 255, 0), 2},   // Lucky Block
        {Color(161, 124, 49), 3},  // Grass
        {Color(101, 49, 19), 4},   // Dirt
        {Color(17, 221, 17), 5},   // Pipe Top Left
        {Color(17, 58, 17), 6},    // Pipe Top Right
        {Color(17, 177, 17), 7},   // Pipe Body Left
        {Color(17, 116, 17), 8},   // Pipe Body Right
        {Color(114, 114, 114), 9}, // Steel
        {Color(255, 255, 255), 10},// Flag Body
        {Color(0, 0, 0), 11}       // Flag Top
    };
}

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

vector<vector<Cell>> Map::getMap() {
    return cellGrid;
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

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            sf::Color color = sketch.getPixel(x, y);
            auto it = colorToType.find(color);
            int type = (it != colorToType.end()) ? it->second : 0;
            cellGrid[x][y] = Cell(x, y, type);
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
    if (cellGrid.empty()) return;

    if (view < 0) view = 0;
    if (view > cellGrid.size() * CELL_SIZE - WIDTH) view = cellGrid.size() * CELL_SIZE - WIDTH;

    int map_start = view / CELL_SIZE;
    int map_end = map_start + WIDTH / CELL_SIZE;
    int map_height = cellGrid[0].size();

    for (int y = 0; y < map_height; ++y) {
        for (int x = map_start; x < map_end; ++x) {
            int type = cellGrid[x][y].getType();
            if (type >= 0 && type < textures.size() && textures[type].getSize().x > 0) {
                Sprite cell;
                cell.setTexture(textures[type]);
                cell.setPosition(x * CELL_SIZE - view, y * CELL_SIZE);
                window.draw(cell);
            }
        }
    }
}