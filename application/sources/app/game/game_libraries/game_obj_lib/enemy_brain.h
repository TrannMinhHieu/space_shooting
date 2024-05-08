#ifndef ENEMY_BRAIN_H
#define ENEMY_BRAIN_H

#include <stdio.h>

#include "fsm.h"
#include "port.h"
#include "message.h"
#include "timer.h"

#include "app.h"
#include "app_dbg.h"
#include "task_list.h"
#include "task_display.h"

/**
 * @brief All enemy auto decide action implemented here.
 *
 * @details This is the brain of the enemy ship. It is responsible for randomizing the action of the enemy ship.
 * There are 4 possible actions: MOVE_UP, MOVE_DOWN, FIRE, and DO_NOTHING.
 * Currently, the enemy ship action is decided RANDOMLY.
 *
 * @todo Improve decision making algorithm.
 *
 * @note Imlemented function need to be call in <sst_enemy_ship.cpp>.
 */

// Implementaion -----------------------------------
uint8_t ship_action;
enum Actions
{
    MOVE_UP,
    MOVE_DOWN,
    FIRE,
    DO_NOTHING
};
/**
 * @brief Randomizes the action for the enemy ship.
 *
 * @details This function generates a random number between 0 and 99 and assigns a action to the enemy ship based on the generated number.
 * @param: None
 * @return: The action for the enemy ship. Possible values are MOVE_UP, MOVE_DOWN, FIRE, or DO_NOTHING.
 */
int8_t randomize_enemy_ship_control()
{
    // TODO: use better randomize function

    uint8_t random = rand() % 100;

    // 5% chance to move up
    // 5% chance to move down
    // 7% chance to fire
    // TODO: increase these chances as the game progresses
    uint16_t rate = (myShip.fly_speed - 1) * 2;
    if (random < 5 + rate)
    {
        task_post_pure_msg(ENEMY_SHIP_TASK_ID, ENEMY_SHIP_MOVE_SIG);
        return MOVE_UP;
    }
    else if (random < 10 + rate)
    {
        task_post_pure_msg(ENEMY_SHIP_TASK_ID, ENEMY_SHIP_MOVE_SIG);
        return MOVE_DOWN;
    }
    else if (random < 17 + rate)
    {
        task_post_pure_msg(ENEMY_SHIP_TASK_ID, ENEMY_SHIP_FIRE_SIG);
        return FIRE;
    }

    return DO_NOTHING;
}

/**
 * @brief Determines the enemy ship's action based on player's relative position.
 *
 * @details Decides enemy action using a strategy influenced by the player's y-coordinate. 
 * Actions include moving up or down with a 60% chance, firing with a 20% chance, or doing nothing. 
 * The decision interval is adjusted based on player speed and randomized between 10 and 14 frames.
 *
 * @return The action for the enemy ship: MOVE_UP, MOVE_DOWN, FIRE, or DO_NOTHING.
 */
uint8_t strategy_based_enemy_decide_action()
{
    static uint8_t decision_interval = 0;
    int random_factor = rand() % 100; // Random number between 0 and 99

    if (decision_interval == 0)
    {
        if (myShip.ship.y < myEnemyShip.ship.y)
        {
            if (random_factor < 60) // 60% chance to move up if player is above
            {
                task_post_pure_msg(ENEMY_SHIP_TASK_ID, ENEMY_SHIP_MOVE_SIG);
                return MOVE_UP;
            }
            else if (random_factor < 80) // 20% chance to fire if player is above
            {
                task_post_pure_msg(ENEMY_SHIP_TASK_ID, ENEMY_SHIP_FIRE_SIG);
                return FIRE;
            }
        }
        else if (myShip.ship.y > myEnemyShip.ship.y)
        {
            if (random_factor < 60) // 60% chance to move down if player is below
            {
                task_post_pure_msg(ENEMY_SHIP_TASK_ID, ENEMY_SHIP_MOVE_SIG);
                return MOVE_DOWN;
            }
            else if (random_factor < 80) // 20% chance to fire if player is below
            {
                task_post_pure_msg(ENEMY_SHIP_TASK_ID, ENEMY_SHIP_FIRE_SIG);
                return FIRE;
            }
        }
        else
        {
            // Player is at the same y-coordinate, decide whether to fire or not with some randomness
            if (random_factor < 20) // 20% chance to fire when player is at the same y-coordinate
            {
                task_post_pure_msg(ENEMY_SHIP_TASK_ID, ENEMY_SHIP_FIRE_SIG);
                return FIRE;
            }
        }

        decision_interval = (rand() % 5 + 10) - (myShip.fly_speed - 1); // Randomize decision interval between 10 and 14 frames, reduce interval based on player speed
    }
    else
    {
        decision_interval--;
    }

    return DO_NOTHING;
}

/**
 * @brief Determines enemy ship's action based on player's relative position and game difficulty.
 *
 * @details Calculates action probabilities for moving up, down, or firing, adjusted by player-enemy position and game state. 
 * Randomizes decision intervals influenced by player speed.
 *
 * @return Enemy action: MOVE_UP, MOVE_DOWN, FIRE, or DO_NOTHING.
 */
uint8_t better_random_enemy_decide_action()
{
    static uint8_t decision_interval = 0;
    int8_t relative_player_enemy_position = myShip.ship.y - myEnemyShip.ship.y; // Pre-calculate relative player-enemy position

    if (decision_interval == 0)
    {
        // TODO: take in Player(x, y) and Enemy(x, y) as parameter to generate random number
        uint8_t random_factor = rand() % 100; // Random number between 0 and 99
        uint8_t base_probability = 20 + myShip.fly_speed;

        // Vary action probabilities based on game state or difficulty level
        uint8_t move_up_probability = base_probability;   // Base probability for moving up
        uint8_t move_down_probability = base_probability; // Base probability for moving down
        uint8_t fire_probability = base_probability - 10; // Base probability for firing

        // Adjust probabilities based on relative position
        if (relative_player_enemy_position < -10)
        {
            // Player is significantly above, bias towards moving up or firing
            move_up_probability += 30;
            move_down_probability -= 10;
            fire_probability += 10;
        }
        else if (relative_player_enemy_position > 10)
        {
            // Player is significantly below, bias towards moving down or firing
            move_up_probability -= 10;
            move_down_probability += 30;
            fire_probability += 10;
        }
        else
        {
            // Player is at a similar level, bias towards firing
            fire_probability += 20;
        }

        // Determine action based on probabilities
        if (random_factor < move_up_probability)
        {
            task_post_pure_msg(ENEMY_SHIP_TASK_ID, ENEMY_SHIP_MOVE_SIG);
            ship_action = MOVE_UP;
        }
        else if (random_factor < move_up_probability + move_down_probability)
        {
            task_post_pure_msg(ENEMY_SHIP_TASK_ID, ENEMY_SHIP_MOVE_SIG);
            ship_action = MOVE_DOWN;
        }
        else if (random_factor < move_up_probability + move_down_probability + fire_probability)
        {
            task_post_pure_msg(ENEMY_SHIP_TASK_ID, ENEMY_SHIP_FIRE_SIG);
            ship_action = FIRE;
        }
        else
        {
            ship_action = DO_NOTHING;
        }
        // Reset decision interval and update previous player position
        decision_interval = (rand() % 10 + 9) - (myShip.fly_speed - 1); // Random base interval between 9 and 18 frames, depending on player speed
        APP_DBG_SIG("Decision interval: %d\n", decision_interval);
    }
    else
    {
        decision_interval--;
        APP_DBG_SIG("Decision interval: %d\n", decision_interval);
    }

    return ship_action;
}

extern uint8_t ship_action;

#endif // ENEMY_BRAIN_H