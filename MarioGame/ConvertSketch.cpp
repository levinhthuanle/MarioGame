#include "ConvertSketch.h"
#include "Items.h"
#include "Global.h"

void convertSketch(string lv, Map& new_map, vector<GameObject*> enemies, vector<GameObject*> items) {
    if (lv == "1-1") {
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
            {Color(0, 0, 0), 0},       // Empty
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

        // Load textures for the level
        if (!new_map.loadTexture("Resources/Stages/1/brick.png", 1) ||
            !new_map.loadTexture("Resources/Stages/1/luckyblock.png", 2) ||
            !new_map.loadTexture("Resources/Stages/1/grass.png", 3) ||
            !new_map.loadTexture("Resources/Stages/1/dirt.png", 4) ||
            !new_map.loadTexture("Resources/Stages/1/pipetopleft.png", 5) ||
            !new_map.loadTexture("Resources/Stages/1/pipetopright.png", 6) ||
            !new_map.loadTexture("Resources/Stages/1/pipebodyleft.png", 7) ||
            !new_map.loadTexture("Resources/Stages/1/pipebodyright.png", 8) ||
            !new_map.loadTexture("Resources/Stages/1/steel.png", 9) ||
            !new_map.loadTexture("Resources/Stages/1/flagbody.png", 10) ||
            !new_map.loadTexture("Resources/Stages/1/flagtop.png", 11)) {
            cerr << "Failed to load textures!" << endl;
            return;
        }
        cout << "Textures loaded" << endl;

        new_map.readSketch("Resources/Stages/1/sketch.png");

        cout << "Map loaded" << endl;
        
        sf::Image sketch;
        if (!sketch.loadFromFile("Resources/Stages/1/sketch.png")) {
            cerr << "Error loading resources" << endl;
        }

        int width = sketch.getSize().x;
        int height = sketch.getSize().y;

        vector<vector<Sprite>>& spriteGrid = new_map.getSpriteGrid();

        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                sf::Color color = sketch.getPixel(x, y);
                if (color == Color(0, 0, 255)) {
                    Items* item = new Items("./Resources/Item/coin.png", "false");
                    item->m_sprite.setPosition(x * CELL_SIZE, y * CELL_SIZE);
                    item->m_sprite.setScale(SCALE, SCALE);
                    spriteGrid[x][y] = item->m_sprite;
                    items.push_back(item);
                }
            }
        }
    }
}