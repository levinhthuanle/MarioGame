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
    int type; // 0 = empty, 1 = brick, 2 = lucky block, 3 = grass, 4 = dirt, 5 = pipe top left, 6 = pipe top right, 7 = pipe body left, 8 = pipe body right, 9 = steel, 10 = flag body, 11 = flag top
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

//Sample usage
//#include "Map.h"
//int main() {
//    RenderWindow window(VideoMode(800, 240), "Mario Game");
//
//	Map map;
//  map.loadTexture("C:/C++/Sem2Year1/MarioGame/MarioGame/MarioGame/Resources/Stages/1-1/background.png", 0);
//	map.loadTexture("C:/C++/Sem2Year1/MarioGame/MarioGame/MarioGame/Resources/Stages/1-1/brick.png", 1);
//	map.loadTexture("C:/C++/Sem2Year1/MarioGame/MarioGame/MarioGame/Resources/Stages/1-1/luckyblock.png", 2);
//	map.loadTexture("C:/C++/Sem2Year1/MarioGame/MarioGame/MarioGame/Resources/Stages/1-1/grass.png", 3);
//	map.loadTexture("C:/C++/Sem2Year1/MarioGame/MarioGame/MarioGame/Resources/Stages/1-1/dirt.png", 4);
//	map.loadTexture("C:/C++/Sem2Year1/MarioGame/MarioGame/MarioGame/Resources/Stages/1-1/pipetopleft.png", 5);
//	map.loadTexture("C:/C++/Sem2Year1/MarioGame/MarioGame/MarioGame/Resources/Stages/1-1/pipetopright.png", 6);
//	map.loadTexture("C:/C++/Sem2Year1/MarioGame/MarioGame/MarioGame/Resources/Stages/1-1/pipebodyleft.png", 7);
//	map.loadTexture("C:/C++/Sem2Year1/MarioGame/MarioGame/MarioGame/Resources/Stages/1-1/pipebodyright.png", 8);
//	map.loadTexture("C:/C++/Sem2Year1/MarioGame/MarioGame/MarioGame/Resources/Stages/1-1/steel.png", 9);
//	map.loadTexture("C:/C++/Sem2Year1/MarioGame/MarioGame/MarioGame/Resources/Stages/1-1/flagbody.png", 10);
//	map.loadTexture("C:/C++/Sem2Year1/MarioGame/MarioGame/MarioGame/Resources/Stages/1-1/flagtop.png", 11);
//
//    cout << "Textures loaded" << endl;
//
//	map.readSketch("C:/C++/Sem2Year1/MarioGame/MarioGame/MarioGame/Resources/Stages/1-1/1-1-sketch.png");
//
//    cout << "Map loaded" << endl;
//
//	int view = 0;
//
//    while (window.isOpen()) {
//		Event event;
//        while (window.pollEvent(event)) {
//            if (event.type == Event::Closed) {
//				window.close();
//			}
//		}
//
//		window.clear(Color::Cyan);
//		map.drawMap(view, window);
//		window.display();
//	}
//
//	return 0;
//}