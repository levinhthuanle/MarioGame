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
