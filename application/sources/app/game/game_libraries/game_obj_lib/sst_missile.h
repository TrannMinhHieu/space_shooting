#ifndef __MISSILE_H__
#define __MISSILE_H__

#include <stdio.h>
#include <vector>

#include "fsm.h"
#include "port.h"
#include "message.h"
#include "timer.h"

#include "app.h"
#include "app_dbg.h"
#include "task_list.h"
#include "task_display.h"

#include "buzzer.h"

#include "sst_game_screen.h"

// Global missile-related constants
#define MAX_PLAYER_MISSILE_DISTANCE     (120)
#define PLAYER_MISSILE_SPEED            (5)
#define SIZE_MISSILE_BITMAP_X           (10)
#define SIZE_MISSILE_BITMAP_Y           (5)
#define SAFE_DISTANCE_TO_FIRE_MISSILE   (80)

#define MAX_NUM_OF_ENEMY_MISSILE        (5)
#define BASE_NUM_OF_ENEMY_MISSILE       (5)

// Local missile-related constants
const uint8_t SHIP_Y_OFFSET_FOR_MISSILES = 5;

typedef struct 
{
    bool visible;
    uint32_t x, y;
    uint8_t action_image;
} Missile;

//extern Missile myEnemyMissile[MAX_NUM_OF_ENEMY_MISSILE];
extern Missile myMissile;
extern std::vector<Missile> v_myEnemyMissiles;

#endif /* __MISSILE_H__ */