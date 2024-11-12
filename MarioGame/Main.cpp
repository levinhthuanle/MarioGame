//#include "Game.h"
//int main()
//{
//    Game* game = new Game();
//
//    game->run();
//
//    delete game;
//    return 0;
//}

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace sf;

class Cell {
private:
    int x;
    int y;
    int type; // 0 = empty, 1 = brick, 2 = lucky block, 3 = grass, 4 = dirt, 5 = pipe top left, 6 = pipe top right, 7 = pipe body left, 8 = pipe body right, 9 = steel, 10 = flag body, 11 = flag top
    bool breakable;
    bool collectable;
public:
    Cell(): x(-1), y(-1), type(0), breakable(false), collectable(false) {}

    Cell(int x, int y, int type, bool breakable, bool collectable) {
		this->x = x;
		this->y = y;
		this->type = type;
		this->breakable = breakable;
		this->collectable = collectable;
	}

	int getX() {
		return x;
	}

	int getY() {
		return y;
	}

	int getType() {
		return type;
	}

	bool isBreakable() {
		return breakable;
	}

	bool isCollectable() {
		return collectable;
	}
};

class Map {
private:
    vector<vector<Cell>> map;
    vector<Texture> textures;
public:
    Map() {
        textures = vector<Texture>(50);
    };

    Map(vector<vector<Cell>> map) {
		this->map = map;
	}

	vector<vector<Cell>> getMap() {
		return map;
	}

    void setMap(vector<vector<Cell>> map) {
		this->map = map;
	}

    void addCell(Cell cell) {
		map[cell.getX()][cell.getY()] = cell;
	}

    void removeCell(int x, int y) {
		map[x][y] = Cell(x, y, 0, false, false);
	}

    void removeCell(Cell cell) {
		map[cell.getX()][cell.getY()] = Cell(cell.getX(), cell.getY(), 0, false, false);
	}

    void clearMap() {
		for (int i = 0; i < map.size(); i++) {
			for (int j = 0; j < map[i].size(); j++) {
				map[i][j] = Cell(i, j, 0, false, false);
			}
		}
	}

    bool readSketch(string sketch_file_name) {
        sf::Image sketch;
        if (!sketch.loadFromFile(sketch_file_name)) {
            cerr << "Error loading " << sketch_file_name << endl;
            return 0;
        }

        int width = sketch.getSize().x;
        int height = sketch.getSize().y;

        map = vector<vector<Cell>>(width, vector<Cell>(height));

        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                sf::Color color = sketch.getPixel(x, y);

                if (color == sf::Color(254, 138, 24)) {
                    map[x][y] = Cell(x, y, 1, true, false);
                }
                else if (color == sf::Color(255, 255, 0)) {
                    map[x][y] = Cell(x, y, 2, false, true);
                }
                else if (color == sf::Color(161, 124, 49)) {
                    map[x][y] = Cell(x, y, 3, false, false);
                }
                else if (color == sf::Color(101, 49, 19)) {
                    map[x][y] = Cell(x, y, 4, false, false);
                }
                else if (color == sf::Color(17, 221, 17)) {
                    map[x][y] = Cell(x, y, 5, false, false);
                }
                else if (color == sf::Color(17, 58, 17)) {
                    map[x][y] = Cell(x, y, 6, false, false);
                }
                else if (color == sf::Color(17, 177, 17)) {
                    map[x][y] = Cell(x, y, 7, false, false);
                }
                else if (color == sf::Color(17, 116, 17)) {
                    map[x][y] = Cell(x, y, 8, false, false);
                }
                else if (color == sf::Color(114, 114, 114)) {
                    map[x][y] = Cell(x, y, 9, false, false);
                }
                else if (color == sf::Color(255, 255, 255)) {
                    map[x][y] = Cell(x, y, 10, false, false);
                }
                else if (color == sf::Color(0, 0, 0)) {
                    map[x][y] = Cell(x, y, 11, false, false);
                }
            }
        }
        return 1;
    }

    bool loadTexture(string texture_file_name, int type) {
		Texture texture;
		if (!texture.loadFromFile(texture_file_name)) {
			cerr << "Error loading " << texture_file_name << endl;
			return 0;
		}
		textures[type] = texture;
		return 1;
	}

    int SCREEN_WIDTH = 800;
    int CELL_SIZE = 16;

    void drawMap(int view, RenderWindow& window) {
        int map_start = view;
        int map_end = (view + SCREEN_WIDTH) / CELL_SIZE;
        int map_height = map[0].size();

        for (int y = 0; y < map_height; y++) {
            for (int x = map_start; x < map_end; x++) {
                Sprite cell;
                cell.setTexture(textures[map[x][y].getType()]);
                cell.setPosition(x * CELL_SIZE, y * CELL_SIZE);
                window.draw(cell);
            }
        }
    }
};

int main() {
    RenderWindow window(VideoMode(800, 240), "Mario Game");

	Map map;
    map.loadTexture("C:/C++/Sem2Year1/MarioGame/MarioGame/MarioGame/Resources/Stages/1-1/background.png", 0);
	map.loadTexture("C:/C++/Sem2Year1/MarioGame/MarioGame/MarioGame/Resources/Stages/1-1/brick.png", 1);
	map.loadTexture("C:/C++/Sem2Year1/MarioGame/MarioGame/MarioGame/Resources/Stages/1-1/luckyblock.png", 2);
	map.loadTexture("C:/C++/Sem2Year1/MarioGame/MarioGame/MarioGame/Resources/Stages/1-1/grass.png", 3);
	map.loadTexture("C:/C++/Sem2Year1/MarioGame/MarioGame/MarioGame/Resources/Stages/1-1/dirt.png", 4);
	map.loadTexture("C:/C++/Sem2Year1/MarioGame/MarioGame/MarioGame/Resources/Stages/1-1/pipetopleft.png", 5);
	map.loadTexture("C:/C++/Sem2Year1/MarioGame/MarioGame/MarioGame/Resources/Stages/1-1/pipetopright.png", 6);
	map.loadTexture("C:/C++/Sem2Year1/MarioGame/MarioGame/MarioGame/Resources/Stages/1-1/pipebodyleft.png", 7);
	map.loadTexture("C:/C++/Sem2Year1/MarioGame/MarioGame/MarioGame/Resources/Stages/1-1/pipebodyright.png", 8);
	map.loadTexture("C:/C++/Sem2Year1/MarioGame/MarioGame/MarioGame/Resources/Stages/1-1/steel.png", 9);
	map.loadTexture("C:/C++/Sem2Year1/MarioGame/MarioGame/MarioGame/Resources/Stages/1-1/flagbody.png", 10);
	map.loadTexture("C:/C++/Sem2Year1/MarioGame/MarioGame/MarioGame/Resources/Stages/1-1/flagtop.png", 11);

    cout << "Textures loaded" << endl;

	map.readSketch("C:/C++/Sem2Year1/MarioGame/MarioGame/MarioGame/Resources/Stages/1-1/1-1-sketch.png");

    cout << "Map loaded" << endl;

	int view = 0;

    while (window.isOpen()) {
		Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
				window.close();
			}
		}

		window.clear(Color::Cyan);
		map.drawMap(view, window);
		window.display();
	}

	return 0;
}