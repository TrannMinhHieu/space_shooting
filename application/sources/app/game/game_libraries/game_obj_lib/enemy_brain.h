#ifndef __ENEMY_BRAIN_H__
#define __ENEMY_BRAIN_H__

#include <stdio.h>
#include <chrono>
#include <thread>

#include "fsm.h"
#include "port.h"
#include "message.h"
#include "timer.h"

#include "app.h"
#include "app_dbg.h"
#include "task_list.h"
#include "task_display.h"

extern uint8_t ship_action;
enum Actions
{
    MOVE_UP,
    MOVE_DOWN,
    FIRE,
    DO_NOTHING
};

extern uint8_t simple_randomize_enemy_control();
extern uint8_t strategy_based_enemy_control();
extern uint8_t better_randomize_enemy_control();
extern uint8_t better_strategy_based_enemy_control();

#endif // ENEMY_BRAIN_H