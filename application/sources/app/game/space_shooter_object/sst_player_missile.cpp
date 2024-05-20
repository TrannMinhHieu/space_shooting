#include "sst_missile.h"

Missile_t myMissile;

bool is_armed();
bool player_missile_enemy_ship_collision();

/**
 * @brief Initialize the missile with default values.
 *
 * @param None
 * @return None
 */
void player_missile_inint()
{
    APP_DBG_SIG("Missile init\n");
    myMissile.x = 0;
    myMissile.y = 0;
    myMissile.visible = BLACK;
    myMissile.action_image = 1;
}

/**
 * @brief Fire the missile if it is armed.
 *
 * This funciton set the y-coordinate of the missile and make it visible.
 *
 * @param None
 * @return None
 */
void player_missile_fired()
{
    // Check if the missile is armed
    if (!is_armed())
    {
        return;
    }
    APP_DBG_SIG("Missile fired\n");
    // Set the y-coordinate of the missile
    myMissile.y = myShip.ship.y + SHIP_Y_OFFSET_FOR_MISSILES;
    myMissile.visible = WHITE;
}

/**
 * @brief Move the missile if it is visible.
 *
 * This funciton moves the missile if it is visible.
 *
 * @param None
 * @return None
 */
void player_missile_flight()
{
    if (myMissile.visible == WHITE)
    {
        if (myMissile.x < MAX_PLAYER_MISSILE_DISTANCE)
        {
            myMissile.x += PLAYER_MISSILE_SPEED; // Move the missile by "PLAYER_MISSILE_SPEED" pixels
        }
        // If the missile fly to "MAX_MISSILE_DISTANCE", reset it
        else if (myMissile.x >= MAX_PLAYER_MISSILE_DISTANCE)
        {
            myMissile.visible = BLACK;
            is_armed(); // Display missile armed message
            myMissile.x = 0;
        }
    }
}

void player_missile_hit()
{
    // Check if there is a collision between the player's missile and the enemy ship
    if (player_missile_enemy_ship_collision())
    {
        APP_DBG_SIG("Missile hit enemy ship\n");
        
        // Set explosion properties
        myExplosion.visible = WHITE;
        myExplosion.x = myMissile.x;
        myExplosion.y = myMissile.y;

        // Hide the player's missile and reset its position
        myMissile.visible = BLACK;
        myMissile.x = 0;
        is_armed();

        // Decrement enemy ship health and print the current value
        myEnemyShip.health--;
        APP_DBG_SIG("Enemy ship health %d\n", myEnemyShip.health);
    }
}

/**
 * @brief Reset the missile.
 *
 * @param None
 * @return None
 */
void player_missile_reset()
{
    APP_DBG_SIG("Missile reset\n");
    myMissile.visible = BLACK;
    myMissile.x = 0;
    myMissile.y = 0;
}

/**
 * @brief Handle the message of the missile.
 *
 * @param msg The message to be handled.
 * @return None
 */
void sst_player_missile_handler(ak_msg_t *msg)
{
    switch (msg->sig)
    {
    case SST_MISSILE_INIT_SIG:
        player_missile_inint();
        break;
    case SST_MISSILE_FIRE_SIG:
        player_missile_fired();
        break;
    case SST_MISSILE_FLIGHT_SIG:
        player_missile_flight();
        break;
    case SST_MISSILE_HIT_SIG:
        player_missile_hit();
        break;
    case SST_MISSILE_RESET_SIG:
        player_missile_reset();
        break;
    default:
        break;
    }
}

// Non-void functions implementation ----------------------------------------------------------
/**
 * Checks if the missile is armed.
 *
 * @param None
 * @return True if the missile is armed, False otherwise.
 */
bool is_armed()
{
    // If the missile is visible it is not armed
    if (myMissile.visible == BLACK)
    {
        APP_DBG_SIG("Missile is armed\n");
        return true; // It is armed
    }
    return false; // Otherwise, it is not armed
}
/**
 * @brief Check if there is a collision between the player's missile and the enemy ship.
 *
 * @return True if there is a collision, False otherwise.
 */
bool player_missile_enemy_ship_collision()
{
    // Check if the enemy ship and the player's missile are both visible.
    if (myEnemyShip.ship.visible != WHITE || myMissile.visible != WHITE)
    {
        return false;
    }

    // Check if the y-coordinate of the missile minus the offset is equal to the y-coordinate of the enemy ship.
    if (myMissile.y - SHIP_Y_OFFSET_FOR_MISSILES != myEnemyShip.ship.y)
    {
        return false;
    }

    // Check if the x-coordinate of the missile plus the size of the missile bitmap is equal to the x-coordinate of the enemy ship.
    if (myMissile.x + SIZE_BITMAP_MISSILE_X <= myEnemyShip.ship.x)
    {
        return false;
    }

    if (myMissile.x > myEnemyShip.ship.x + SIZE_BITMAP_SHIP_X)
    {
        return false;
    }

    // If all conditions are met, return true
    return true;
}