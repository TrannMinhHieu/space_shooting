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

// Global ship-related constants
#define SHIP_Y_STEP             (10)
#define SIZE_BITMAP_SHIP_X      (15)
#define SIZE_BITMAP_SHIP_Y      (15)
#define SHIP_X_COORDINATE       (0)
#define SHIP_Y_COORDINATE       (0)

#define SHIP_LIFE               (3)

typedef struct 
{
    bool visible;
    uint32_t x, y;
    uint8_t action_image;
    // uint8_t fly_speed;
    // uint32_t score;
} Ship;

typedef struct
{
    Ship ship;
    uint8_t fly_speed;
    uint32_t score;
} PlayerShip;

typedef struct
{
    Ship ship;
    uint8_t health;
    uint8_t num_missiles;
} EnemyShip;

extern PlayerShip myShip;
extern EnemyShip myEnemyShip;

#endif /* __SHIP_H__ */