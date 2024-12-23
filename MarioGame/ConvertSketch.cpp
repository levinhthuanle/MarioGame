#include "ConvertSketch.h"
#include "Items.h"
#include "Global.h"

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
        {11, {false, false}}  // Flag Top
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
        {Color(0, 0, 0), 11}       // Flag Top
    };

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
    cout << "Textures loaded" << endl;

    cout << "Map loaded" << endl;
    sf::Image sketch;
    if (lv == "1-1") {
        if (!sketch.loadFromFile("Resources/Stages/1/sketch_edited.png")) {
            cerr << "Error loading resources" << endl;
        }
        else {
            cout << "Sketch 1 loaded" << endl;
        }
    }
    else if (lv == "1-2") {
        if (!sketch.loadFromFile("Resources/Stages/2/sketch_edited.png")) {
			cerr << "Error loading resources" << endl;
		}
        else {
            cout << "Sketch 2 loaded" << endl;
        }
    }

    int width = sketch.getSize().x;
    int height = sketch.getSize().y;

    objMap = vector<vector<GameObject*>>(width, vector<GameObject*>(height, nullptr));
    vector<vector<Cell>>& cellGrid = new_map.getMap();
    vector<vector<Sprite*>>& spriteGrid = new_map.getSpriteGrid();

    cellGrid = vector<vector<Cell>>(width, vector<Cell>(height, Cell()));
    spriteGrid = vector<vector<Sprite*>>(width, vector<Sprite*>(height, nullptr));

    int count = 0;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            count++;
            cout << count << endl;
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
                GameObject* luckyblock = new GameObject("Resources/Tile/luckyblock.png");
                luckyblock->m_name = "Lucky Block";
                luckyblock->m_sprite.setPosition(x * CELL_SIZE, y * CELL_SIZE);
                luckyblock->m_sprite.setScale(SCALE, SCALE);
                spriteGrid[x][y] = &luckyblock->m_sprite;
                gameObjects.push_back(luckyblock);
                luckyblocks.push_back(luckyblock);
                objMap[x][y] = luckyblock;
            }
            else {
                spriteGrid[x][y] = new Sprite(textures[type]);
                spriteGrid[x][y]->setPosition(x * CELL_SIZE, y * CELL_SIZE);
                spriteGrid[x][y]->setScale(SCALE, SCALE);
                objMap[x][y] = nullptr;
            }
            if (color == Color(0, 0, 255)) {
                Items* item = new Items("./Resources/Item/coin0.png", "./Resources/Item/coin1.png", "false");\
                item->m_name = "Coin";
                item->m_sprite.setPosition(x * CELL_SIZE, y * CELL_SIZE);
                item->m_sprite.setScale(SCALE, SCALE);
                spriteGrid[x][y] = &item->m_sprite;
                items.push_back(item);
                objMap[x][y] = item;
            }
            if (color == Color(101, 19, 19)) {
                GameObject* enemy = new GameObject(); //Change to Enemy class if nesscessary
                enemy->m_name = "Enemy";
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
    cout<< "Sketch converted" << endl;
}