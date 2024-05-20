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

#include "sst_game_screen.h"

#include "buzzer.h"

#define NUM_ASTEROIDS                       (6)
#define SIZE_BITMAP_ASTEROIDS_X             (20)
#define SIZE_BITMAP_ASTEROIDS_Y             (10)

// Define global asteroid y-coordinates
#define ASTEROID_0_Y_COORDINATE             (3)
#define ASTEROID_1_Y_COORDINATE             (13)
#define ASTEROID_2_Y_COORDINATE             (23)
#define ASTEROID_3_Y_COORDINATE             (33)
#define ASTEROID_4_Y_COORDINATE             (43)
#define ASTEROID_5_Y_COORDINATE             (53)

// Local values
// Define offsets
const int MISSILE_Y_OFFSET_FOR_ASTEROID = 2;
const int SHIP_Y_OFFSET_FOR_ASTEROID = 3;

// Predefined y-coordinates for each asteroid
const int asteroidYCoordinates[NUM_ASTEROIDS] = {ASTEROID_0_Y_COORDINATE,
                                                 ASTEROID_1_Y_COORDINATE,
                                                 ASTEROID_2_Y_COORDINATE,
                                                 ASTEROID_3_Y_COORDINATE,
                                                 ASTEROID_4_Y_COORDINATE,
                                                 ASTEROID_5_Y_COORDINATE};

typedef struct
{
    bool visible;
    int32_t x, y;
    uint8_t action_image;
    const uint8_t asteroid_score = 10;
} Asteroid_t;

extern Asteroid_t myAsteroid[NUM_ASTEROIDS];

#endif /* __ASTEROID_H__ */