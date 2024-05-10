#ifndef __GAME_SCREEN__
#define __GAME_SCREEN__

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
#include "task_list.h"

#include "eeprom.h"
#include "app_eeprom.h"

#include "buzzer.h"

#include "sst_game_highscore.h"
#include "sst_game_bitmap.h"

#include "sst_ship.h"
#include "sst_asteroid.h"
#include "sst_missile.h"
#include "sst_explosion.h"

#define GAME_OFF    (0)
#define GAME_PLAY   (1)
#define GAME_OVER   (2)

#define GAME_STAGE_SHIP_FIGHT		(0)
#define GAME_STAGE_ASTEROID_FEILD	(1)

// global game state
extern uint8_t game_state;
extern uint8_t game_stage;

extern view_dynamic_t dyn_view_sst_game_screen;
extern view_screen_t sst_game_screen;
extern void game_screen_handler(ak_msg_t* msg);

#endif // GAME_SCREEN