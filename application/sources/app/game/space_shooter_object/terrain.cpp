#include "terrain.h"
#include <vector>

using namespace std;

std::vector<TerrainCoordinates> v_terrain;

TerrainCoordinates::TerrainCoordinates() {
    this->x = rand() % (LCD_WIDTH - 10);
    this->y = rand() % (LCD_HEIGHT - 10);
}

void TerrainCoordinates::terrainMover() {
    this->x = this->x - 1;

    if (this->x < 0) {
        this->x = rand() % (LCD_WIDTH - 10);
        this->y = rand() % (LCD_HEIGHT - 10);
    }
}

void terrain_generate() {
    for(int i = 0; i < 10; i++) {
        v_terrain.push_back(TerrainCoordinates());
    }
}

void terrain_update() {
    for (uint8_t i = 0; i < v_terrain.size(); i++) {
        v_terrain[i].terrainMover();
        if(v_terrain[i].x < 0) {
            v_terrain[i].x = rand() % (LCD_WIDTH - 10);
            v_terrain[i].y = rand() % (LCD_HEIGHT - 10);
        }
    }
}