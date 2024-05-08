#include "terrain.h"
#include <vector>

struct point
{
    int x;
    int y;
};

void generate_terrain()
{
    // TODO: randomize x coordinates
    int y = rand() % 20 + 10;
    int x = 120;

    point p = {x, y};
    v_terrain.push_back(p);
}

std::vector<point> v_terrain;
void update_terrain()
{
    // TODO: update terrain
    // store in a vector with x and y coordinates
    // x = x + 1;
    // draw on screen

    for (int i = 0; i < v_terrain.size(); i++)
    {
        v_terrain[i].x = v_terrain[i].x + 1;

        if (v_terrain[i].x < 10)
        {
            v_terrain.erase(v_terrain.begin() + i);
        }
    }
}