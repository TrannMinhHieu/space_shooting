#ifndef __MISSILE_H__
#define __MISSILE_H__

#include <stdio.h>

#include "fsm.h"
#include "port.h"
#include "message.h"
#include "timer.h"

#include "app.h"
#include "app_dbg.h"
#include "task_list.h"
#include "task_display.h"

#include "buzzer.h"

#include "game_screen.h"

// Global missile-related constants
#define MAX_MISSILE_DISTANCE    (120)
#define MISSILE_SPEED           (5)
#define SIZE_MISSILE_BITMAP_X   (10)
#define SIZE_MISSILE_BITMAP_Y   (5)

typedef struct 
{
    bool visible;
    uint32_t x, y;
    uint8_t action_image;
} Missile;

extern Missile myMissile;

#endif /* __MISSILE_H__ */