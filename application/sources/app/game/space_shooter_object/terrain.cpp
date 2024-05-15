#include "terrain.h"
#include <vector>

using namespace std;

bool is_terrain_out_of_screen(int terrain_index);

std::vector<TerrainCoordinates> v_terrain;
TerrainCoordinates::TerrainCoordinates()
{
    this->x = 140;
    // TODO: intergrate perlin noise for smoother terrain
    this->y = (rand() % 30) + 30;
}
TerrainCoordinates::TerrainCoordinates(int x, int y)
{
    this->x = x;
    this->y = y;
}
void TerrainCoordinates::terrainMover()
{
    this->x = this->x - myShip.fly_speed;
}

void terrain_init()
{
    APP_DBG_SIG("Terrain init\n");
    v_terrain.push_back(TerrainCoordinates(140, 60));
    v_terrain.push_back(TerrainCoordinates(160, 50));
}

void terrain_generate()
{
    v_terrain.push_back(TerrainCoordinates());
    APP_DBG_SIG("Terrain size %d\n", v_terrain.size());
}

void terrain_end();
static int generated = 0;
void terrain_update()
{
    static int x_coord_tracker;
    // RAM overflow
    for (uint8_t i = 0; i < v_terrain.size(); i++)
    {
        v_terrain[i].terrainMover();
        x_coord_tracker = v_terrain.back().x;
        APP_DBG_SIG("x_coord_tracker %d\n", x_coord_tracker);

        if (generated == 20)
        {
            // TODO: reset counter to 0
            terrain_end();
            break;
        }
        else if (x_coord_tracker < LCD_WIDTH + 2 && v_terrain.size() < TERRAIN_MAX_LENGTH)
        {
            terrain_generate();
            generated++;
            APP_DBG_SIG("Generated %d\n", generated);
            break;
        }
        if (is_terrain_out_of_screen(i))
        {
            v_terrain.erase(v_terrain.begin() + i);
            APP_DBG_SIG("Terrain size %d\n", v_terrain.size());
        }
    }
}

void terrain_end()
{
    static bool done = false;
    if (!done)
    {
        v_terrain.push_back(TerrainCoordinates(155, 50));
        v_terrain.push_back(TerrainCoordinates(180, 60));
        done = true;
    }

    if (v_terrain.size() <= 1)
    {
        APP_DBG_SIG("Terrain end\n");
        task_post_pure_msg(TERRAIN_TASK_ID, TERRAIN_RESET_SIG);
        task_post_pure_msg(ASTEROID_TASK_ID, ASTEROID_SPAWN_SIG);
        generated = 0;
        game_stage = GAME_STAGE_ASTEROID_FEILD;
    }

    for (uint8_t i = 0; i < v_terrain.size(); i++)
    {
        v_terrain[i].terrainMover();

        if (is_terrain_out_of_screen(i))
        {
            v_terrain.erase(v_terrain.begin() + i);
            APP_DBG_SIG("Terrain size %d\n", v_terrain.size());
        }
    }
}

void terrain_reset()
{
    APP_DBG_SIG("Terrain reset\n");
    v_terrain.clear();
}

void terrain_handler(ak_msg_t *msg)
{
    switch (msg->sig)
    {
    case TERRAIN_INIT_SIG:
        terrain_init();
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

bool terrain_ship_collision(int terrain_index)
{
    if (v_terrain[terrain_index].y < (int)myShip.ship.y)
    {
        return true;
    }

    return false;
}

bool is_terrain_out_of_screen(int terrain_index)
{
    if (v_terrain[terrain_index].x < -15)
    {
        return true;
    }
    return false;
}