#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>

using namespace std;
using namespace sf;

struct ColorComparator {
    bool operator()(const sf::Color& lhs, const sf::Color& rhs) const {
        if (lhs.r != rhs.r)
            return lhs.r < rhs.r;
        if (lhs.g != rhs.g)
            return lhs.g < rhs.g;
        if (lhs.b != rhs.b)
            return lhs.b < rhs.b;
        return lhs.a < rhs.a;
    }
};

struct CellProperties {
    bool breakable;
    bool collectable;
};

class Cell {
private:
    int x;
    int y;
    int type;
public:
    Cell();
    Cell(int x, int y, int type);

    int getX() const;
    int getY() const;
    int getType() const;
};

class Map {
private:
    vector<vector<Cell>> cellGrid;
    vector<Texture> textures;
    map<int, CellProperties> cellProperties;
    map<Color, int, ColorComparator> colorToType;

public:
    Map();
    Map(const std::map<int, CellProperties>& cellProps,
        const std::map<sf::Color, int, ColorComparator>& colorMap);

    bool isBreakable(const Cell& cell) const;
    bool isCollectable(const Cell& cell) const;

    vector<vector<Cell>> getMap();
    void setMap(vector<vector<Cell>> map);

    void addCell(Cell cell);
    void removeCell(int x, int y);
    void clearMap();

    bool readSketch(string sketch_file_name);
    bool loadTexture(string texture_file_name, int type);

    void drawMap(int view, RenderWindow& window);
};

Map loadMap(string lv);

//Sample usage
//#include "Map.h"
//#include <iostream>
//
//using namespace std;
//using namespace sf;
//
//int main() {
//    //level 1-1
//    RenderWindow window(VideoMode(800, 240), "Mario Game");
//
//    // Initialize cell properties and color-to-type mappings
//    map<int, CellProperties> cellProperties = {
//        {0, {true, false}},
//        {1, {true, false}},   // Brick
//        {2, {false, true}},   // Lucky Block
//        {3, {false, false}},  // Grass
//        {4, {false, false}},  // Dirt
//        {5, {false, false}},  // Pipe Top Left
//        {6, {false, false}},  // Pipe Top Right
//        {7, {false, false}},  // Pipe Body Left
//        {8, {false, false}},  // Pipe Body Right
//        {9, {false, false}},  // Steel
//        {10, {false, false}}, // Flag Body
//        {11, {false, false}}  // Flag Top
//    };
//
//    map<Color, int, ColorComparator> colorToType = {
//        {Color(254, 138, 24), 1},  // Brick
//        {Color(255, 255, 0), 2},   // Lucky Block
//        {Color(161, 124, 49), 3},  // Grass
//        {Color(101, 49, 19), 4},   // Dirt
//        {Color(17, 221, 17), 5},   // Pipe Top Left
//        {Color(17, 58, 17), 6},    // Pipe Top Right
//        {Color(17, 177, 17), 7},   // Pipe Body Left
//        {Color(17, 116, 17), 8},   // Pipe Body Right
//        {Color(114, 114, 114), 9}, // Steel
//        {Color(255, 255, 255), 10},// Flag Body
//        {Color(0, 0, 0), 11}       // Flag Top
//    };
//
//    // Create the map with specific properties
//    Map map(cellProperties, colorToType);
//
//    // Load textures for the level
//    if (!map.loadTexture("Resources/Stages/1-1/background.png", 0) ||
//        !map.loadTexture("Resources/Stages/1-1/brick.png", 1) ||
//        !map.loadTexture("Resources/Stages/1-1/luckyblock.png", 2) ||
//        !map.loadTexture("Resources/Stages/1-1/grass.png", 3) ||
//        !map.loadTexture("Resources/Stages/1-1/dirt.png", 4) ||
//        !map.loadTexture("Resources/Stages/1-1/pipetopleft.png", 5) ||
//        !map.loadTexture("Resources/Stages/1-1/pipetopright.png", 6) ||
//        !map.loadTexture("Resources/Stages/1-1/pipebodyleft.png", 7) ||
//        !map.loadTexture("Resources/Stages/1-1/pipebodyright.png", 8) ||
//        !map.loadTexture("Resources/Stages/1-1/steel.png", 9) ||
//        !map.loadTexture("Resources/Stages/1-1/flagbody.png", 10) ||
//        !map.loadTexture("Resources/Stages/1-1/flagtop.png", 11)) {
//        cerr << "Failed to load textures!" << endl;
//        return -1;
//    }
//    cout << "Textures loaded" << endl;
//
//    // Load the sketch for the level
//    if (!map.readSketch("Resources/Stages/1-1/1-1-sketch.png")) {
//        cerr << "Failed to load map sketch!" << endl;
//        return -1;
//    }
//    cout << "Map loaded" << endl;

//    Map map = loadMap("1-1");
//
//    // Main game loop
//    int view = 0;
//    while (window.isOpen()) {
//        Event event;
//        while (window.pollEvent(event)) {
//            if (event.type == Event::Closed) {
//                window.close();
//            }
//        }
//
//        window.clear(Color::Cyan);
//        map.drawMap(view, window);
//        window.display();
//    }
//
//    return 0;
//}
