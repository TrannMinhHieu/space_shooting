#ifndef __SST_GAME_STARTUP_H__
#define __SST_GAME_STARTUP_H__

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

#include "sst_game_screen.h"
#include "sst_game_menu.h"

#include "buzzer.h"

extern view_dynamic_t dyn_view_sst_game_startup;
extern view_screen_t sst_game_startup;
extern void sst_game_startup_handler(ak_msg_t* msg);

#endif // SST_GAME_STARTUP_H