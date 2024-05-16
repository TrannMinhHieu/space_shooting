#ifndef __TASK_LIST_H__
#define __TASK_LIST_H__

#include "ak.h"
#include "task.h"

extern const task_t app_task_table[];
extern const task_polling_t app_task_polling_table[];

/*****************************************************************************/
/*  DECLARE: Internal Task ID
 *  Note: Task id MUST be increasing order.
 */
/*****************************************************************************/
enum {
	/* SYSTEM TASKS */
	TASK_TIMER_TICK_ID,

	/* APP TASKS */
	AC_TASK_SYSTEM_ID,
	AC_TASK_FW_ID,
	AC_TASK_SHELL_ID,
	AC_TASK_LIFE_ID,
	AC_TASK_IF_ID,
	AC_TASK_UART_IF_ID,
	AC_TASK_DISPLAY_ID,

	/* GAME TASKS*/
	SST_ASTEROID_TASK_ID,
	SST_EXPLOSION_TASK_ID,
	SST_TERRAIN_TASK_ID,

	SST_PLAYER_SHIP_TASK_ID,
	SST_PLAYER_MISSILE_TASK_ID,

	SST_ENEMY_SHIP_TASK_ID,
	SST_ENEMY_MISSILE_TASK_ID,
	
	SST_GAMEPLAY_TASK_ID,

	/* LINK */
#if defined (IF_LINK_UART_EN)
	AC_LINK_PHY_ID,
	AC_LINK_MAC_ID,
	AC_LINK_ID,
#endif

	/* EOT task ID */
	AK_TASK_EOT_ID,
};

/*****************************************************************************/
/*  DECLARE: Internal Polling Task ID
 *  Note: Task id MUST be increasing order.
 */
/*****************************************************************************/
enum {
	/* APP TASKS */
	AC_TASK_POLLING_CONSOLE_ID,

	/* EOT polling task ID */
	AK_TASK_POLLING_EOT_ID,
};

/*****************************************************************************/
/*  DECLARE: Task entry point
 */
/*****************************************************************************/
/* APP TASKS */
extern void task_system(ak_msg_t*);
extern void task_fw(ak_msg_t*);
extern void task_shell(ak_msg_t*);
extern void task_life(ak_msg_t*);
extern void task_if(ak_msg_t*);
extern void task_uart_if(ak_msg_t*);
extern void task_display(ak_msg_t*);

/* GAME TASKS */
// Common object handler
extern void sst_asteroid_handler(ak_msg_t*);
extern void sst_explosion_handler(ak_msg_t*);
extern void sst_terrain_handler(ak_msg_t*);

// Player object handler
extern void sst_player_ship_handler(ak_msg_t*);
extern void sst_player_missile_handler(ak_msg_t*);

// Enemy object handler
extern void sst_enemy_missile_handler(ak_msg_t*);
extern void sst_enemy_ship_handler(ak_msg_t*);

// Game play handler
extern void sst_game_play_handler(ak_msg_t*);

/* LINK TASK */
extern void task_link_phy(ak_msg_t*);
extern void task_link_mac(ak_msg_t*);
extern void task_link(ak_msg_t*);

/*****************************************************************************/
/*  DECLARE: Task polling
 */
/*****************************************************************************/
extern void task_polling_console();

#endif //__TASK_LIST_H__
