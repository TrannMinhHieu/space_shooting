#ifndef __GAME_MENU_H__
#define __GAME_MENU_H__

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

#include "eeprom.h"
#include "app_eeprom.h"

#include "sst_game_screen.h"
#include "sst_game_highscore.h"
#include "sst_game_bitmap.h"

extern view_dynamic_t dyn_view_game_menu;
extern view_screen_t game_menu;
extern void game_menu_handler(ak_msg_t* msg);

#endif /* __GAME_MENU_H__ */