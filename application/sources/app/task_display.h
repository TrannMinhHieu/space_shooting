#ifndef __TASK_DISPLAY_H__
#define __TASK_DISPLAY_H__

#include "screen_manager.h"
#include "sst_game_startup.h"
#include "sst_game_idle.h"

#define LCD_WIDTH			 (124)
#define LCD_HEIGHT			 (60)
#define SCREEN_LEFT_BOUNDARY (0)

#define NUMFLAKES			 (10)
#define XPOS				 (0)
#define YPOS				 (1)
#define DELTAY				 (2)
#define LOGO16_GLCD_HEIGHT	 (16)
#define LOGO16_GLCD_WIDTH	 (16)

extern scr_mng_t scr_mng_app;

extern void scr_startup_handle(ak_msg_t* msg);
extern void sst_game_startup_handler(ak_msg_t* msg);
extern void sst_game_idle_handler(ak_msg_t* msg);

#endif // __TASK_DISPLAY_H__
