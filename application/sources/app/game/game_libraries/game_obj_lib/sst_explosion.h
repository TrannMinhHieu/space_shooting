#ifndef __EXPLOSION_H__
#define __EXPLOSION_H__

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

#define SIZE_BITMAP_EXPLOSION_X     (15)
#define SIZE_BITMAP_EXPLOSION_Y     (15)

typedef struct 
{
    bool visible;
    uint8_t x, y;
    uint8_t action_image;
} sst_Explosion_t;

extern sst_Explosion_t myExplosion;

#endif /* __EXPLOSION_H__ */