#ifndef __GAME_HIGHSCORE_H__
#define __GAME_HIGHSCORE_H__

#include "fsm.h"
#include "port.h"
#include "message.h"
#include "timer.h"

#include "sys_ctrl.h"
#include "sys_dbg.h"

#include "eeprom.h"
#include "app_eeprom.h"

#include "app.h"
#include "app_dbg.h"
#include "task_list.h"
#include "task_display.h"
#include "view_render.h"

#include "sst_game_menu.h"

extern view_dynamic_t dyn_view_sst_game_highscore;
extern view_screen_t sst_game_highscore;

typedef struct
{
    uint32_t current_score;
    uint32_t first_place;
    uint32_t second_place;
    uint32_t third_place;
} game_score_t;

extern game_score_t sst_game_score;

extern void sst_game_highscore_handler(ak_msg_t* msg);

#endif /* __GAME_HIGHSCORE_H__ */