#ifndef __SHIP_H__
#define __SHIP_H__

#include <stdio.h>

#include "fsm.h"
#include "port.h"
#include "message.h"
#include "timer.h"

#include "app.h"
#include "app_dbg.h"
#include "task_list.h"
#include "task_display.h"

#include "game_screen.h"

//global ship-related constants
#define STEP_SHIP_AXIS_Y        (10)
#define SIZE_BITMAP_SHIP_X      (15)
#define SIZE_BITMAP_SHIP_Y      (15)
#define AXIS_SHIP_X             (0)
#define AXIS_SHIP_Y             (0)

typedef struct 
{
    bool visible;
    uint32_t x, y;
    uint8_t action_image;
    uint32_t score;
} Ship;

extern Ship myShip;

#endif /* __SHIP_H__ */