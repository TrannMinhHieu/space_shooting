#ifndef __SST_SHIP_H__
#define __SST_SHIP_H__

#include <stdio.h>

#include "fsm.h"
#include "port.h"
#include "message.h"
#include "timer.h"

#include "app.h"
#include "app_dbg.h"
#include "task_list.h"
#include "task_display.h"

#include "sst_game_screen.h"

// Global ship-related constants
#define SHIP_Y_STEP             (10)
#define SIZE_BITMAP_SHIP_X      (15)
#define SIZE_BITMAP_SHIP_Y      (15)
#define SHIP_X_COORDINATE       (0)
#define SHIP_Y_COORDINATE       (20)

#define SHIP_LIFE               (3)
#define BASE_NUM_OF_ENEMY_MISSILE       (12)

typedef struct 
{
    bool visible;
    uint32_t x, y;
    uint8_t action_image;
} Ship_t;

typedef struct
{
    Ship_t ship;
    uint8_t fly_speed;
    uint32_t score;
} PlayerShip_t;

typedef struct
{
    Ship_t ship;
    uint8_t health;
    uint8_t num_missiles;
    const uint8_t enemy_ship_score = 100;
} EnemyShip_t;

extern PlayerShip_t myShip;
extern EnemyShip_t myEnemyShip;

#endif /* __SST_SHIP_H__ */