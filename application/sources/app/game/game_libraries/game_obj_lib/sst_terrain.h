#ifndef __TERRAIN_H__
#define __TERRAIN_H__

#include <stdio.h>
#include <vector>

#include "fsm.h"
#include "port.h"
#include "message.h"
#include "timer.h"

#include "sys_ctrl.h"
#include "sys_dbg.h"

#include "app.h"
#include "app_dbg.h"
#include "task_list.h"
#include "task_display.h"
#include "view_render.h"

#define TERRAIN_MAX_LENGTH (12)
class TerrainCoordinates
{
public:
    int x;
    int y;
    static const int terrain_score;

    TerrainCoordinates();
    TerrainCoordinates(int x, int y);

    void terrainMover();
};

extern std::vector<TerrainCoordinates> v_terrain;

#endif // TERRAIN_H