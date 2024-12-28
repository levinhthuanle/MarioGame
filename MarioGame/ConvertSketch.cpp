#include "ConvertSketch.h"
#include "Items.h"
#include "Global.h"
#include "Coins.h"
#include "Mushroom.h"
#include "LuckyBlock.h"
#include "Enemy.h"

void convertSketch(string lv, Map& new_map, vector<vector<GameObject*>>& objMap, vector<GameObject*>& gameObjects, vector<GameObject*>& bricks, vector<GameObject*>& luckyblocks, vector<GameObject*>& enemies, vector<GameObject*>& items, Sprite& character) {
    map<int, CellProperties> cellProperties = {
        {0, {true, true}},    // Empty
        {1, {true, false}},   // Brick
        {2, {false, true}},   // Lucky Block
        {3, {false, false}},  // Grass
        {4, {false, false}},  // Dirt
        {5, {false, false}},  // Pipe Top Left
        {6, {false, false}},  // Pipe Top Right
        {7, {false, false}},  // Pipe Body Left
        {8, {false, false}},  // Pipe Body Right
        {9, {false, false}},  // Steel
        {10, {false, false}}, // Flag Body
        {11, {false, false}},  // Flag Top
        {12, {false, true}},  // Mushroom
        {13, {false, false}}   // Dead
    };

    map<Color, int, ColorComparator> colorToType = {
        {Color(0, 0, 0, 0), 0},    // Empty
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
        {Color(0, 0, 0), 11},       // Flag Top
        {Color(208, 148, 56), 12}, // Mushroom
        {Color(255, 0, 255), 13} //Dead
    };

    GoombaFactory goombaFactory;
    KoopaFactory koopaFactory;

    // Create the map with specific properties
    new_map = Map(cellProperties, colorToType);

    vector<Texture>& textures = new_map.getTextures();

    // Load textures for the level
    if (!new_map.loadTexture("Resources/Tile/brick.png", 1) ||
        !new_map.loadTexture("Resources/Tile/luckyblock.png", 2) ||
        !new_map.loadTexture("Resources/Tile/grass.png", 3) ||
        !new_map.loadTexture("Resources/Tile/dirt.png", 4) ||
        !new_map.loadTexture("Resources/Tile/pipetopleft.png", 5) ||
        !new_map.loadTexture("Resources/Tile/pipetopright.png", 6) ||
        !new_map.loadTexture("Resources/Tile/pipebodyleft.png", 7) ||
        !new_map.loadTexture("Resources/Tile/pipebodyright.png", 8) ||
        !new_map.loadTexture("Resources/Tile/steel.png", 9) ||
        !new_map.loadTexture("Resources/Tile/flagbody.png", 10) ||
        !new_map.loadTexture("Resources/Tile/flagtop.png", 11)) {
        cerr << "Failed to load textures!" << endl;
        return;
    }
    std::cout << "Textures loaded" << endl;

    std::cout << "Map loaded" << endl;
    sf::Image sketch;
    if (lv == "1-1") {
        if (!sketch.loadFromFile("Resources/Stages/1/sketch_edited.png")) {
            cerr << "Error loading resources" << endl;
        }
        else {
            std::cout << "Sketch 1 loaded" << endl;
        }
    }
    else if (lv == "1-2") {
        if (!sketch.loadFromFile("Resources/Stages/2/sketch_edited.png")) {
			cerr << "Error loading resources" << endl;
		}
        else {
            std::cout << "Sketch 2 loaded" << endl;
        }
    }
    else if (lv == "1-3") {
        if (!sketch.loadFromFile("Resources/Stages/3/sketch_edited.png")) {
            cerr << "Error loading resources" << endl;
        }
        else {
            std::cout << "Sketch 3 loaded" << endl;
        }
    }
    srand(time(0));

    int width = sketch.getSize().x;
    int height = sketch.getSize().y;

    objMap = vector<vector<GameObject*>>(width, vector<GameObject*>(height, nullptr));
    vector<vector<Cell>>& cellGrid = new_map.getMap();
    vector<vector<Sprite*>>& spriteGrid = new_map.getSpriteGrid();

    cellGrid = vector<vector<Cell>>(width, vector<Cell>(height, Cell()));
    spriteGrid = vector<vector<Sprite*>>(width, vector<Sprite*>(height, nullptr));


    int cnt = 0;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            sf::Color color = sketch.getPixel(x, y);
            auto it = colorToType.find(color);
            int type = (it != colorToType.end()) ? it->second : 0;
            cellGrid[x][y] = Cell(x, y, type);
            if (type == 1) {
                GameObject* brick = new GameObject("Resources/Tile/brick.png");
                brick->m_name = "Brick";
                brick->m_sprite.setPosition(x * CELL_SIZE, y * CELL_SIZE);
                brick->m_sprite.setScale(SCALE, SCALE);
                spriteGrid[x][y] = &brick->m_sprite;
                gameObjects.push_back(brick);
                bricks.push_back(brick);
                objMap[x][y] = brick;
            }
            else if (type == 2) {
                int randomNum = rand() % 3 + 1; // Generates a random number between 1 and 2

                bool isLucky = (randomNum == 3) ? 1 : 0;

                GameObject* luckyblock = new LuckyBlock("Resources/Tile/luckyblock.png", "Resources/Tile/steel.png", "Lucky Block", isLucky);
                luckyblock->m_sprite.setPosition(x * CELL_SIZE, y * CELL_SIZE);
                luckyblock->m_sprite.setScale(SCALE, SCALE);
                spriteGrid[x][y] = &luckyblock->m_sprite;
                gameObjects.push_back(luckyblock);
                luckyblocks.push_back(luckyblock);
                objMap[x][y] = luckyblock;
            }
            else if (type == 5) {
                // Pipe top left
                GameObject* pipe = new Pipe(true, { 50, 50 });
                pipe->m_sprite.setPosition(x * CELL_SIZE, y * CELL_SIZE);
                pipe->m_sprite.setScale(SCALE, SCALE);
                spriteGrid[x][y] = &pipe->m_sprite;
                gameObjects.push_back(pipe);
                objMap[x][y] = pipe;
            }
            else if (type == 13) {
                // Dead
                GameObject* dead = new GameObject("Resources/Tile/brick.png");
                dead->m_name = "Dead";
                dead->m_sprite.setPosition(x * CELL_SIZE, y * CELL_SIZE);
                dead->m_sprite.setScale(SCALE, SCALE);
                spriteGrid[x][y] = &dead->m_sprite;
                gameObjects.push_back(dead);
                objMap[x][y] = dead;
            }
            else if (type == 10) {
                // Flag Body
                GameObject* flag = new GameObject("Resources/Tile/flagbody.png");
                flag->m_name = "Flag";
                flag->m_sprite.setPosition(x * CELL_SIZE, y * CELL_SIZE);
                flag->m_sprite.setScale(SCALE, SCALE);
                spriteGrid[x][y] = &flag->m_sprite;
                gameObjects.push_back(flag);
                objMap[x][y] = flag;
            }
            else if (type != 0) {
                spriteGrid[x][y] = new Sprite(textures[type]);
                spriteGrid[x][y]->setPosition(x * CELL_SIZE, y * CELL_SIZE);
                spriteGrid[x][y]->setScale(SCALE, SCALE);
                objMap[x][y] = nullptr;
            }
            else {
                spriteGrid[x][y] = nullptr;
                objMap[x][y] = nullptr;
            }
            if (color == Color(0, 0, 255)) {
                Items* item = new Coins("./Resources/Item/coin1.png", "./Resources/Item/coin2.png", "false");\
                item->m_name = "Coin";
                item->m_sprite.setPosition(x * CELL_SIZE, y * CELL_SIZE);
                item->m_sprite.setScale(SCALE, SCALE);
                spriteGrid[x][y] = &item->m_sprite;
                items.push_back(item);
                objMap[x][y] = item;
            }
            if (color == Color(101, 19, 19)) { 
                GameObject* enemy = goombaFactory.create();
                enemy->m_name = "Goomba";
                cnt++;
				enemy->m_sprite.setPosition(x * CELL_SIZE, y * CELL_SIZE);
				enemy->m_sprite.setScale(SCALE, SCALE);
				spriteGrid[x][y] = &enemy->m_sprite;
				enemies.push_back(enemy);
				objMap[x][y] = enemy;
            }
            if (color == Color(255, 0, 0)) {
				GameObject* enemy = koopaFactory.create();
                enemy->m_name = "Koopa";
                enemy->m_sprite.setPosition(x * CELL_SIZE, y * CELL_SIZE);
				enemy->m_sprite.setScale(SCALE, SCALE);
                spriteGrid[x][y] = &enemy->m_sprite;
				enemies.push_back(enemy);
                objMap[x][y] = enemy;
			}
            if (color == Color(85, 42, 83)) {
				character.setPosition(x * CELL_SIZE, y * CELL_SIZE);
                objMap[x][y] = nullptr;
			}
        }
    }
    std::cout<< "Sketch converted" << endl;
}