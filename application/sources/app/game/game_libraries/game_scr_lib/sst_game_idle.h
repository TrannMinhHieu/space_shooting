#ifndef __SST_GAME_IDLE_H__
#define __SST_GAME_IDLE_H__

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

#include "buzzer.h"

extern view_dynamic_t dyn_view_sst_game_idle;
extern view_screen_t sst_game_idle;
extern void sst_game_idle_handler(ak_msg_t* msg);

#endif