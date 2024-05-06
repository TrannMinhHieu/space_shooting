#include "missile.h"

Missile myMissile;

/**
 * @brief Initialize the missile with default values.
 *
 * @param None
 * @return None
 */
void missile_inint()
{
    APP_DBG_SIG("Missile init\n");
    myMissile.x = 0;
    myMissile.y = 0;
    myMissile.visible = BLACK;
    myMissile.action_image = 1;
}

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
 * @brief Fire the missile if it is armed.
 *
 * This funciton set the y-coordinate of the missile and make it visible.
 *
 * @param None
 * @return None
 */
void missile_fired()
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
void missile_flight()
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

bool missile_enemy_ship_collision() {
    if(myEnemyShip.ship.visible == WHITE && myMissile.visible == WHITE
        && myMissile.x + SIZE_MISSILE_BITMAP_X > myEnemyShip.ship.x
        && myMissile.y - SHIP_Y_OFFSET_FOR_MISSILES == myEnemyShip.ship.y) 
    {
        return true;
    }

    return false;
}
//TODO: fix bug missile_enemy_ship_collision not detected
void missile_hit() {
    if(missile_enemy_ship_collision()) {
        APP_DBG_SIG("Missile hit enemy ship\n");
        myExplosion.visible = WHITE;
        myExplosion.x = myMissile.x;
        myExplosion.y = myMissile.y;
        myMissile.visible = BLACK;
        myMissile.x = 0;
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
void missile_reset()
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
void missile_handler(ak_msg_t* msg)
{
    switch (msg->sig)
    {
    case MISSILE_INIT_SIG:
        missile_inint();
        break;
    case MISSILE_FIRE_SIG:
        missile_fired();
        break;
    case MISSILE_FLIGHT:
        missile_flight();
        break;
    case MISSILE_HIT_SIG:
        missile_hit();
        break;
    case MISSILE_RESET_SIG:
        missile_reset();
        break;
    default:
        break;
    }
}