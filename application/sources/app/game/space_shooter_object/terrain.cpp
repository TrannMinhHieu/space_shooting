#include "terrain.h"
#include <vector>

using namespace std;

std::vector<TerrainCoordinates> v_terrain;

void TerrainCoordinates::coordinates()
{
    this->x = (rand() % 39) + 130;
    this->y = (rand() % 39) + 10;
}

void TerrainCoordinates::terrainMover()
{
    this->x = this->x - 1;
}
void terrain_generate()
{
    uint8_t terrain_size = 10;
    if(v_terrain.size() < terrain_size)
    {
        v_terrain.push_back(TerrainCoordinates());
    }
}

void terrain_update()
{
    for (uint8_t i = 0; i < v_terrain.size(); i++)
    {
        v_terrain[i].terrainMover();
        if(v_terrain[i].x < 0)
        {
            v_terrain.erase(v_terrain.begin() + i);
        }
    }
}

void terrain_reset()
{
    v_terrain.clear();
}

void terrain_handler(ak_msg_t *msg)
{
    switch (msg->sig)
    {
    case TERRAIN_GENERATE_SIG:
        terrain_generate();
        break;
    case TERRAIN_UPDATE_SIG:
        terrain_update();
        break;
    case TERRAIN_RESET_SIG:
        terrain_reset();
        break;
    default:
        break;
    }
}