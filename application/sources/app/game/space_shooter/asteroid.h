#ifndef __ASTEROID_H__
#define __ASTEROID_H__

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

#include "buzzer.h"

#define NUM_ASTEROIDS              (6)
#define SIZE_BITMAP_ASTEROIDS_X    (20)
#define SIZE_BITMAP_ASTEROIDS_Y    (10)
#define ASTEROIDS_SPEED            (5)

#define AXIS_Y_ASTEROID_0          (3)
#define AXIS_Y_ASTEROID_1          (13)
#define AXIS_Y_ASTEROID_2          (23)
#define AXIS_Y_ASTEROID_3          (33)
#define AXIS_Y_ASTEROID_4          (43)
#define AXIS_Y_ASTEROID_5          (53)

const int SCREEN_LEFT_BOUNDARY = 0;

typedef struct {
    bool visible;
    int32_t x, y;
    uint8_t action_image;
} Asteroid;

extern Asteroid myAsteroid[NUM_ASTEROIDS];

#endif /* __ASTEROID_H__ */