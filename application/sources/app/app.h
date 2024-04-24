/**
 ******************************************************************************
 * @author: GaoKong
 * @date:   13/08/2016
 ******************************************************************************
**/

#ifndef __APP_H__
#define __APP_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "ak.h"
#if defined (IF_NETWORK_NRF24_EN)
#include "nrf_nwk_sig.h"
#endif

#include "app_if.h"
#include "app_eeprom.h"
#include "app_data.h"

/*****************************************************************************/
/* SYSTEM task define
 */
/*****************************************************************************/
/* define timer */
/* define signal */
enum {
	SYSTEM_AK_FLASH_UPDATE_REQ = AK_USER_DEFINE_SIG,
};

/*****************************************************************************/
/* FIRMWARE task define
 */
/*****************************************************************************/
/* define timer */
#define FW_PACKED_TIMEOUT_INTERVAL			(5000)
#define FW_UPDATE_REQ_INTERVAL				(5000)

/* define signal */
enum {
	FW_CRENT_APP_FW_INFO_REQ = AK_USER_DEFINE_SIG,
	FW_CRENT_BOOT_FW_INFO_REQ,
	FW_UPDATE_REQ,
	FW_UPDATE_SM_OK,
	FW_TRANSFER_REQ,
	FW_INTERNAL_UPDATE_APP_RES_OK,
	FW_INTERNAL_UPDATE_BOOT_RES_OK,
	FW_SAFE_MODE_RES_OK,
	FW_UPDATE_SM_BUSY,
	FW_PACKED_TIMEOUT,
	FW_CHECKING_REQ
};

/*****************************************************************************/
/*  LIFE task define
 */
/*****************************************************************************/
/* define timer */
#define AC_LIFE_TASK_TIMER_LED_LIFE_INTERVAL		(1000)

/* define signal */
enum {
	AC_LIFE_SYSTEM_CHECK = AK_USER_DEFINE_SIG,
};

/*****************************************************************************/
/*  SHELL task define
 */
/*****************************************************************************/
/* define timer */

/* define signal */
enum {
	AC_SHELL_LOGIN_CMD = AK_USER_DEFINE_SIG,
	AC_SHELL_REMOTE_CMD,
};

/*****************************************************************************/
/*  RF24 task define
 */
/*****************************************************************************/
/* private define */
/* define timer */
/* define signal */
enum {
	AC_RF24_IF_INIT_NETWORK = AK_USER_DEFINE_SIG,
	AC_RF24_IF_PURE_MSG_OUT,
	AC_RF24_IF_COMMON_MSG_OUT,
	AC_RF24_IF_PURE_MSG_IN,
	AC_RF24_IF_COMMON_MSG_IN,
};

/*****************************************************************************/
/* IF task define
 */
/*****************************************************************************/
/* define timer */
/* define signal */
enum {
	AC_IF_PURE_MSG_IN = AK_USER_DEFINE_SIG,
	AC_IF_PURE_MSG_OUT,
	AC_IF_COMMON_MSG_IN,
	AC_IF_COMMON_MSG_OUT,
	AC_IF_DYNAMIC_MSG_IN,
	AC_IF_DYNAMIC_MSG_OUT,
};

/*****************************************************************************/
/* UART_IF task define
 */
/*****************************************************************************/
/* timer signal */
/* define signal */

enum {
	AC_UART_IF_INIT = AK_USER_DEFINE_SIG,
	AC_UART_IF_PURE_MSG_OUT,
	AC_UART_IF_COMMON_MSG_OUT,
	AC_UART_IF_DYNAMIC_MSG_OUT,
	AC_UART_IF_PURE_MSG_IN,
	AC_UART_IF_COMMON_MSG_IN,
	AC_UART_IF_DYNAMIC_MSG_IN,
};

/*****************************************************************************/
/*  LIFE task define
 */
/*****************************************************************************/
/* define timer */
#define AC_DISPLAY_INITIAL_INTERVAL									(100)
#define AC_DISPLAY_STARTUP_INTERVAL									(10000)
#define AC_DISPLAY_LOGO_INTERVAL									(1000)
#define AC_DISPLAY_SHOW_IDLE_BALL_MOVING_UPDATE_INTERAL				(150)
#define AC_DISPLAY_SHOW_MERRY_CHRISTMAS_SNOW_MOVING_UPDATE_INTERAL	(150)
#define AC_DISPLAY_SHOW_MERRY_CHRISTMAS_SLEEP_INTERVAL				(15000)
#define AC_DISPLAY_SHOW_MODBUS_PULL_INTERVAL						(1500)
#define AC_DISPLAY_SHOW_MODBUS_PULL_SLEEP_INTERVAL					(30000)

/* define signal */
enum {
	AC_DISPLAY_INITIAL = AK_USER_DEFINE_SIG,
	AC_DISPLAY_BUTON_MODE_RELEASED,
	AC_DISPLAY_BUTON_UP_RELEASED,
	AC_DISPLAY_BUTON_DOWN_RELEASED,
	AC_DISPLAY_SHOW_LOGO,	
	AC_DISPLAY_SHOW_GAME_PLAY,
	AC_DISPLAY_SHOW_IDLE,
	AC_DISPLAY_SHOW_IDLE_BALL_MOVING_UPDATE,
	AC_DISPLAY_SHOW_FW_UPDATE,
	AC_DISPLAY_SHOW_FW_UPDATE_ERR,
	AC_DISPLAY_SHOW_MERRY_CHRISTMAS_SNOW_MOVING_UPDATE,
	AC_DISPLAY_SHOW_MERRY_CHRISTMAS_SLEEP,
	AC_DISPLAY_SHOW_MODBUS_PULL_UPDATE,
	AC_DISPLAY_SHOW_MODBUS_PULL_SLEEP,
};



/*****************************************************************************/
/*  ZIGBEE task define
 */
/*****************************************************************************/
/* define timer */
/* define signal */
enum {
	AC_ZIGBEE_INIT = AK_USER_DEFINE_SIG,
	AC_ZIGBEE_FORCE_START_COODINATOR,
	AC_ZIGBEE_START_COODINATOR,
	AC_ZIGBEE_PERMIT_JOINING_REQ,
	AC_ZIGBEE_ZCL_CMD_HANDLER
};

/*****************************************************************************/
/* DBG task define
 */
/*****************************************************************************/
/* define timer */
/* define signal */
enum {
	AC_DBG_TEST_1 = AK_USER_DEFINE_SIG,
};

/*****************************************************************************/
/* DISPLAY task define
 */
/*****************************************************************************/
/* define timer */
#define GAMEPLAY_TIME_TICK_INTERVAL (100)
#define GAMEPLAY_TIME_EXIT_INTERVAL (3000)
/* define signal */
enum {
	GAMEPLAY_INITIAL_SETUP = AK_USER_DEFINE_SIG,
	GAMEPLAY_TIME_TICK = GAME_DEFINE_SIG,
	GAME_EXIT
};

/*****************************************************************************/
/*  BUTTON task define
 */
/*****************************************************************************/
/* define timer */
/* define signal */
enum {
	AC_DISPLAY_BUTTON_MODE_PRESSED = 1,						
	AC_DISPLAY_BUTTON_MODE_LONG_PRESSED,					
	AC_DISPLAY_BUTTON_MODE_RELEASED,
	AC_DISPLAY_BUTTON_UP_PRESSED,							
	AC_DISPLAY_BUTTON_UP_LONG_PRESSED,					
	AC_DISPLAY_BUTTON_UP_RELEASED,
	AC_DISPLAY_BUTTON_DOWN_PRESSED,						
	AC_DISPLAY_BUTTON_DOWN_LONG_PRESSED,					
	AC_DISPLAY_BUTTON_DOWN_RELEASED,
};

/*****************************************************************************/
/* SHIP task define
*/
/*****************************************************************************/
enum {
	SHIP_INIT_SIG = AK_USER_DEFINE_SIG,
	SHIP_FLIGHT_SIG,
	SHIP_FIRE_SIG,
	SHIP_MOVE_UP_SIG,
	SHIP_MOVE_DOWN_SIG,
	SHIP_RESET_SIG,
	SHIP_HIT_SIG,
	MISSILE_DESTROY_SIG
};

/*****************************************************************************/
/* MISSILE task define
*/
/*****************************************************************************/
enum {
	MISSILE_INIT_SIG = AK_USER_DEFINE_SIG,
	MISSILE_FIRE_SIG,
	MISSILE_HIT_SIG,
	MISSILE_FLIGHT
};

/*****************************************************************************/
/* ASTEROID task define
*/
/*****************************************************************************/
enum {
	ASTEROID_INIT_SIG = AK_USER_DEFINE_SIG,
	ASTEROID_FLIGHT_SIG,
	ASTEROID_HIT_SIG,
};

/*****************************************************************************/
/* EXPLOSION task define
*/
/*****************************************************************************/
enum {
	EXPLOSION_INIT_SIG = AK_USER_DEFINE_SIG,
	EXPLPOSION_EXPLODE_SIG
};

/*****************************************************************************/
/*  app function declare
 */
/*****************************************************************************/
#define APP_MAGIC_NUMBER	0xAABBCCDD
#define APP_VER				{0, 0, 0, 3}

typedef struct {
	uint32_t magic_number;
	uint8_t version[4];
} app_info_t;

extern const app_info_t app_info;

extern void* app_get_boot_share_data();
extern int  main_app();

#ifdef __cplusplus
}
#endif

#endif //__APP_H__