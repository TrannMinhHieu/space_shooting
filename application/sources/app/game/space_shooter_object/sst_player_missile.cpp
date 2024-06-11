#include "sst_missile.h"

sst_Missile_t myMissile;
std::vector<sst_Missile_t> v_myPlayerMissiles;

uint8_t arm_missile_interval = 0;

bool is_armed();
bool is_player_missile_enemy_ship_collided(uint8_t player_missile_index);

/**
 * @brief Initialize the missile with default values.
 *
 * @param None
 * @return None
 */
void sst_player_missile_inint()
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
void sst_player_missile_fired()
{
    APP_DBG_SIG("interval %d\n", arm_missile_interval);
    // Check if the missile is armed
    if (!is_armed())
    {
        APP_DBG_SIG("Missile not armed\n");
        return;
    }
    APP_DBG_SIG("Missile fired\n");
    // Set the y-coordinate of the missile
    if (v_myPlayerMissiles.size() == 3)
    {
        return;
    }
    myMissile.y = myShip.ship.y + SHIP_Y_OFFSET_FOR_MISSILES;
    myMissile.visible = WHITE;

    v_myPlayerMissiles.push_back(myMissile);
    arm_missile_interval = 3;
}

/**
 * @brief Move the missile if it is visible.
 *
 * This funciton moves the missile if it is visible.
 *
 * @param None
 * @return None
 */
void sst_player_missile_flight()
{
    for (int i = v_myPlayerMissiles.size() - 1; i >= 0; --i)
    {
        if (v_myPlayerMissiles[i].visible == WHITE)
        {
            v_myPlayerMissiles[i].x += PLAYER_MISSILE_SPEED;

            if (v_myPlayerMissiles[i].x >= MAX_PLAYER_MISSILE_DISTANCE)
            {
                v_myPlayerMissiles[i].visible = BLACK;
                v_myPlayerMissiles.erase(v_myPlayerMissiles.begin() + i);
            }
        }
    }

    if (arm_missile_interval > 0)
    {
        arm_missile_interval--;
    }
}

void sst_player_missile_hit()
{
    for (uint8_t i = 0; i < v_myPlayerMissiles.size(); i++)
    {
        // Check if there is a collision between the player's missile and the enemy ship
        if (is_player_missile_enemy_ship_collided(i))
        {
            APP_DBG_SIG("Missile hit enemy ship\n");

            // Set explosion properties
            myExplosion.visible = WHITE;
            myExplosion.x = v_myPlayerMissiles[i].x;
            myExplosion.y = v_myPlayerMissiles[i].y;

            // Hide the player's missile and reset its position
            v_myPlayerMissiles.erase(v_myPlayerMissiles.begin() + i);

            // Decrement enemy ship health and print the current value
            myEnemyShip.health--;
            APP_DBG_SIG("Enemy ship health %d\n", myEnemyShip.health);
        }
    }
}

/**
 * @brief Reset the missile.
 *
 * @param None
 * @return None
 */
void sst_player_missile_reset()
{
    APP_DBG_SIG("Missile reset\n");
    myMissile.visible = BLACK;
    myMissile.x = 0;
    myMissile.y = 0;

    v_myPlayerMissiles.clear();
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
        sst_player_missile_inint();
        break;
    case SST_MISSILE_FIRE_SIG:
        sst_player_missile_fired();
        break;
    case SST_MISSILE_FLIGHT_SIG:
        sst_player_missile_flight();
        sst_player_missile_hit();
        break;
    case SST_MISSILE_RESET_SIG:
        sst_player_missile_reset();
        break;
    default:
        break;
    }
}

// NON-VOID FUNCTIONS IMPLEMENTATION ----------------------------------------------------------
/**
 * Checks if the missile is armed.
 *
 * @param None
 * @return True if the missile is armed, False otherwise.
 */
bool is_armed()
{
    if (arm_missile_interval == 0)
    {
        return true;
    }
    return false;
}
/**
 * @brief Check if there is a collision between the player's missile and the enemy ship.
 *
 * @return True if there is a collision, False otherwise.
 */
bool is_player_missile_enemy_ship_collided(uint8_t player_missile_index)
{
    // Check if the enemy ship and the player's missile are both visible.
    if (myEnemyShip.ship.visible != WHITE || v_myPlayerMissiles[player_missile_index].visible != WHITE)
    {
        return false;
    }

    // Check if the y-coordinate of the missile minus the offset is equal to the y-coordinate of the enemy ship.
    if (v_myPlayerMissiles[player_missile_index].y - SHIP_Y_OFFSET_FOR_MISSILES != myEnemyShip.ship.y)
    {
        return false;
    }

    // Check if the x-coordinate of the missile plus the size of the missile bitmap is equal to the x-coordinate of the enemy ship.
    if (v_myPlayerMissiles[player_missile_index].x + SIZE_BITMAP_MISSILE_X <= myEnemyShip.ship.x)
    {
        return false;
    }

    if (v_myPlayerMissiles[player_missile_index].x > myEnemyShip.ship.x + SIZE_BITMAP_SHIP_X)
    {
        return false;
    }

    // If all conditions are met, return true
    return true;
}