#include "sst_missile.h"

sst_Missile_t myEnemyMissile;
std::vector<sst_Missile_t> v_myEnemyMissiles;

bool is_enemy_missile_out_of_screen(uint8_t enemy_missile_index);
bool is_enemy_missile_player_missile_collided(uint8_t enemy_missile_index);
bool is_enemy_missile_player_ship_collided(uint8_t enemy_missile_index);

// TODO: Missile fire bug
/**
 * @brief enemy missiles by setting their properties to default values.
 *
 * @param None
 * @return None
 *
 * @throws None
 */
void sst_enemy_missile_inint()
{
    // For each element of the v_myEnemyMissiles vector
    for(uint8_t i = 0; i < myEnemyShip.num_missiles; i++)
    {
        // Set the properties of the current element
        myEnemyMissile.visible = BLACK;
        myEnemyMissile.x = 0;
        myEnemyMissile.y = 0;
        myEnemyMissile.action_image = 1;

        // Add the current element to the v_myEnemyMissiles vector
        v_myEnemyMissiles.push_back(myEnemyMissile);
    }
}

/**
 * @brief the collision events when an enemy missile hits either the player's missile or the player's ship.
 *
 * @param None
 * @return None
 *
 * @throws None
 */
/**
 * Handles the collision events when an enemy missile hits either the player's missile or the player's ship.
 */
void sst_enemy_missile_hit()
{
    // Iterate over each element of the v_myEnemyMissiles vector
    for (uint8_t i = 0; i < v_myEnemyMissiles.size(); i++)
    {
        // Check if there is a collision between the enemy missile and the player's missile
        if (is_enemy_missile_player_missile_collided(i))
        {
            APP_DBG_SIG("Enemy missile hit missile\n");

            // Set the visibility of the explosion to white and update its position to the enemy missile's position
            myExplosion.visible = WHITE;
            myExplosion.x = v_myEnemyMissiles[i].x;
            myExplosion.y = v_myEnemyMissiles[i].y;

            // Set the visibility of the enemy missile and the player's missile to black
            v_myEnemyMissiles[i].visible = BLACK;
            myMissile.visible = BLACK;

            // Reset the position of the player's missile and update the enemy missile's position to the enemy ship's position
            myMissile.x = 0;
            v_myEnemyMissiles[i].x = myEnemyShip.ship.x;
        }

        // Check if there is a collision between the enemy missile and the player's ship
        if (is_enemy_missile_player_ship_collided(i))
        {
            APP_DBG_SIG("Enemy missile hit ship\n");
            APP_DBG_SIG("Ship hited by enemy missile no %d\n", i);

            // Set the visibility of the explosion to white and update its position to the player's ship's position
            myExplosion.visible = WHITE;
            myExplosion.x = myShip.ship.x;
            myExplosion.y = myShip.ship.y;

            // Set the visibility of the enemy missile and the player's ship to black
            v_myEnemyMissiles[i].visible = BLACK;
            myShip.ship.visible = BLACK;

            // Send a message to the gameplay task to exit the game
            task_post_pure_msg(SST_GAMEPLAY_TASK_ID, GAME_EXIT);
        }
    }
}

// TODO: missile have to travel "x" pixels before it can be fire again

/**
 * @brief Fires an enemy missile by setting its properties to make it visible and positioned at the enemy ship's location.
 *
 * @param None
 * @return none
 *
 * @throws None
 */
void sst_enemy_missile_fired()
{
    // Iterate over each element of the v_myEnemyMissiles vector
    for (uint8_t i = 0; i < v_myEnemyMissiles.size(); i++)
    {
        // Check if the current enemy missile is not visible (color is black)
        if (v_myEnemyMissiles[i].visible == BLACK)
        {
            // Set the properties of the missile to make it visible and positioned at the enemy ship's location
            v_myEnemyMissiles[i].x = myEnemyShip.ship.x;
            v_myEnemyMissiles[i].y = myEnemyShip.ship.y + SHIP_Y_OFFSET_FOR_MISSILES;
            v_myEnemyMissiles[i].visible = WHITE;

            // Print debug message
            APP_DBG_SIG("Enemy missile[%d] fired at (%d, %d)\n", i, v_myEnemyMissiles[i].x, v_myEnemyMissiles[i].y);

            // Exit the loop
            break;
        }
    }
}

/**
 * @brief Updates the flight of enemy missiles on the screen.
 *
 * @return void
 * @throws None
 */
void sst_enemy_missile_flight()
{
    // Iterate over each enemy missile
    for (uint8_t i = 0; i < v_myEnemyMissiles.size(); i++)
    {
        // Check if the current enemy missile is visible
        if (v_myEnemyMissiles[i].visible == WHITE)
        {
            // Decrement the x-coordinate by the ship's fly speed
            v_myEnemyMissiles[i].x -= myShip.fly_speed;

            // Check if the enemy missile is out of the screen
            if (is_enemy_missile_out_of_screen(i))
            {
                APP_DBG_SIG("Enemy missile[%d] out of screen\n", i);
                // Reset the enemy missile's visibility
                v_myEnemyMissiles[i].visible = BLACK;
            }
        }
    }
}

/**
 * @brief Resets the properties of all enemy missiles to their default values.
 *
 * @param None
 * @return None
 *
 * @throws None
 */
void sst_enemy_missile_reset()
{
    // Clear the v_myEnemyMissiles vector
    v_myEnemyMissiles.clear();
}

/**
 * @brief Handles the messages received by the enemy missile object.
 *
 * @param msg The message to be handled.
 * @return None.
 *
 * @throws None.
 */
void sst_enemy_missile_handler(ak_msg_t *msg)
{
    switch (msg->sig)
    {
    case SST_ENEMY_MISSILE_INIT_SIG:
        sst_enemy_missile_inint();
        break;
    case SST_ENEMY_MISSILE_FIRE_SIG:
        sst_enemy_missile_fired();
        break;
    case SST_ENEMY_MISSILE_FLIGHT_SIG:
        sst_enemy_missile_flight();
        sst_enemy_missile_hit();
        break;
    case SST_ENEMY_MISSILE_RESET_SIG:
        sst_enemy_missile_reset();
        break;
    default:
        break;
    }
}

// NON-VOID FUNCTIONS IMPLEMENTATION ----------------------------------------------------------
/**
 * @brief if the enemy missile at the given index is out of the screen.
 *
 * @param enemy_missile_index the index of the enemy missile to check
 * @return true if the enemy missile is out of the screen, false otherwise
 */
bool is_enemy_missile_out_of_screen(uint8_t enemy_missile_index)
{
    if ((int8_t)(v_myEnemyMissiles[enemy_missile_index].x + SIZE_BITMAP_MISSILE_X) < SCREEN_LEFT_BOUNDARY)
    {
        return true;
    }

    return false;
}
/**
 * @brief Checks if the player's missile collides with an enemy missile.
 *
 * @param enemy_missile_index the index of the enemy missile to check collision with
 * @return true if the player's missile collides with the enemy missile, false otherwise
 *
 * @throws None
 */
bool is_enemy_missile_player_missile_collided(uint8_t enemy_missile_index)
{
    // Check if myMissile and myEnemyMissile are both visible and at the same y position
    if (myMissile.visible != WHITE || v_myEnemyMissiles[enemy_missile_index].visible != WHITE)
    {
        return false;
    };
    // Check if the y positions of the player missile and the enemy missile with offset overlap
    if (myMissile.y != v_myEnemyMissiles[enemy_missile_index].y)
    {
        return false;
    };

    // Check if the x positions of the missiles overlap
    if (myMissile.x + SIZE_BITMAP_MISSILE_X <= v_myEnemyMissiles[enemy_missile_index].x)
    {
        return false;
    };

    // If all conditions are met, return true
    return true;
}
bool is_enemy_missile_player_ship_collided(uint8_t enemy_missile_index)
{
    // Check if the ship and the enemy missile are both visible
    if (myShip.ship.visible != WHITE || v_myEnemyMissiles[enemy_missile_index].visible != WHITE)
    {
        return false;
    };
    // Check if the y positions of the ship and the enemy missile with offset overlap
    if (myShip.ship.y != v_myEnemyMissiles[enemy_missile_index].y - SHIP_Y_OFFSET_FOR_MISSILES)
    {
        return false;
    };

    // Check if the x positions of the ship and the enemy missile overlap
    if (myShip.ship.x + SIZE_BITMAP_SHIP_X <= v_myEnemyMissiles[enemy_missile_index].x)
    {
        return false;
    };

    // If all conditions are met, return true
    return true;
}
