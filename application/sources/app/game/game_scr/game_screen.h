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

#include "game_bitmap.h"

#include "ship.h"
#include "asteroid.h"
#include "missile.h"
#include "explosion.h"

#define GAME_OFF    (0)
#define GAME_PLAY   (1)
#define GAME_OVER   (2)

// global game state
extern uint8_t game_state;

extern view_dynamic_t dyn_view_game;
extern view_screen_t game_screen;
extern void game_screen_handler(ak_msg_t* msg);

#endif // GAME_SCREEN