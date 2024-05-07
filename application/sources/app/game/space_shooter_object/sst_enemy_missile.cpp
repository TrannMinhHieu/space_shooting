#include "sst_missile.h"

Missile myEnemyMissile[MAX_NUM_OF_ENEMY_MISSILE];

bool is_enemy_missile_out_of_screen(uint8_t enemy_missile_index);
bool enemy_missile_player_missile_collision(uint8_t enemy_missile_index);
bool enemy_missile_player_ship_collision(uint8_t enemy_missile_index);

/**
 * @brief enemy missiles by setting their properties to default values.
 *
 * @param None
 * @return None
 *
 * @throws None
 */
void enemy_missile_inint()
{
    // Iterate over each element of the myEnemyMissile array
    for (uint8_t i = 0; i < MAX_NUM_OF_ENEMY_MISSILE; i++)
    {
        // Set the properties of the current element
        myEnemyMissile[i].visible = BLACK;
        myEnemyMissile[i].x = 0;
        myEnemyMissile[i].y = 0;
        myEnemyMissile[i].action_image = 1;
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
void enemy_missile_hit()
{
    // Iterate over each element of the myEnemyMissile array
    for (uint8_t i = 0; i < MAX_NUM_OF_ENEMY_MISSILE; i++)
    {
        // Check if there is a collision between the enemy missile and the player's missile
        if (enemy_missile_player_missile_collision(i))
        {
            APP_DBG_SIG("Enemy missile hit missile\n");

            // Set the visibility of the explosion to white and update its position to the enemy missile's position
            myExplosion.visible = WHITE;
            myExplosion.x = myEnemyMissile[i].x;
            myExplosion.y = myEnemyMissile[i].y;

            // Set the visibility of the enemy missile and the player's missile to black
            myEnemyMissile[i].visible = BLACK;
            myMissile.visible = BLACK;

            // Reset the position of the player's missile and update the enemy missile's position to the enemy ship's position
            myMissile.x = 0;
            myEnemyMissile[i].x = myEnemyShip.ship.x;

            // Increment the number of enemy missiles
            myEnemyShip.num_missiles++;
        }

        // Check if there is a collision between the enemy missile and the player's ship
        if (enemy_missile_player_ship_collision(i))
        {
            // TODO: fix bug collision not detected
            APP_DBG_SIG("Enemy missile hit ship\n");
            APP_DBG_SIG("Ship hited by enemy missile no %d\n", i);
            APP_DBG_SIG("Enemy missile no %d position x = %d y = %d\n", i, myEnemyMissile[i].x, myEnemyMissile[i].y);

            // Set the visibility of the explosion to white and update its position to the player's ship's position
            myExplosion.visible = WHITE;
            myExplosion.x = myShip.ship.x;
            myExplosion.y = myShip.ship.y;

            // Set the visibility of the enemy missile and the player's ship to black
            myEnemyMissile[i].visible = BLACK;
            myShip.ship.visible = BLACK;

            // Send a message to the gameplay task to exit the game
            task_post_pure_msg(GAMEPLAY_TASK_ID, GAME_EXIT);
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
void enemy_missile_fired()
{
    // Iterate over each element of the myEnemyMissile array
    for (uint8_t i = 0; i < MAX_NUM_OF_ENEMY_MISSILE; i++)
    {
        // Check if the current enemy missile is not visible (color is black)
        if (myEnemyMissile[i].visible == BLACK)
        {
            // Set the properties of the missile to make it visible and positioned at the enemy ship's location
            myEnemyMissile[i].x = myEnemyShip.ship.x;
            myEnemyMissile[i].y = myEnemyShip.ship.y + SHIP_Y_OFFSET_FOR_MISSILES;
            myEnemyMissile[i].visible = WHITE;

            // Print debug message
            APP_DBG_SIG("Enemy missile fired\n");

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
void enemy_missile_flight()
{
    // Iterate over each enemy missile
    for (uint8_t i = 0; i < MAX_NUM_OF_ENEMY_MISSILE; i++)
    {
        // Check if the current enemy missile is visible
        if (myEnemyMissile[i].visible == WHITE)
        {
            // Decrement the x-coordinate by the ship's fly speed
            myEnemyMissile[i].x -= myShip.fly_speed;

            // Check if the enemy missile is out of the screen
            if (is_enemy_missile_out_of_screen(i))
            {
                // Reset the enemy missile's visibility
                myEnemyMissile[i].visible = BLACK;
                // myEnemyMissile[i].x = myEnemyShip.ship.x;
                // myEnemyMissile[i].y = myEnemyShip.ship.y + SHIP_Y_OFFSET_FOR_MISSILES;

                // Increment the number of enemy missiles
                myEnemyShip.num_missiles++;
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
void enemy_missile_reset()
{
    for (uint8_t i = 0; i < MAX_NUM_OF_ENEMY_MISSILE; i++)
    {
        // Set the visibility of the current enemy missile to black.
        myEnemyMissile[i].visible = BLACK;

        // Set the x-coordinate and y-coordinate of the current enemy missile to 0.
        myEnemyMissile[i].x = 0;
        myEnemyMissile[i].y = 0;

        // Set the action image of the current enemy missile to 1.
        myEnemyMissile[i].action_image = 1;
    }
}

/**
 * @brief Handles the messages received by the enemy missile object.
 *
 * @param msg The message to be handled.
 * @return None.
 *
 * @throws None.
 */
void enemy_missile_handler(ak_msg_t *msg)
{
    switch (msg->sig)
    {
    case ENEMY_MISSILE_INIT_SIG:
        enemy_missile_inint();
        break;
    case ENEMY_MISSILE_FIRE_SIG:
        enemy_missile_fired();
        break;
    case ENEMY_MISSILE_FLIGHT_SIG:
        enemy_missile_flight();
        break;
    case ENEMY_MISSILE_HIT_SIG:
        enemy_missile_hit();
        break;
    case ENEMY_MISSILE_RESET_SIG:
        enemy_missile_reset();
        break;
    default:
        break;
    }
}

// Non-void functions implementation ----------------------------------------------------------
/**
 * @brief if the enemy missile at the given index is out of the screen.
 *
 * @param enemy_missile_index the index of the enemy missile to check
 * @return true if the enemy missile is out of the screen, false otherwise
 */
bool is_enemy_missile_out_of_screen(uint8_t enemy_missile_index)
{
    if ((int8_t)(myEnemyMissile[enemy_missile_index].x + SIZE_MISSILE_BITMAP_X) < SCREEN_LEFT_BOUNDARY)
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
bool enemy_missile_player_missile_collision(uint8_t enemy_missile_index)
{
    // Check if myMissile and myEnemyMissile are both visible and at the same y position
    if (myMissile.visible != WHITE || myEnemyMissile[enemy_missile_index].visible != WHITE)
    {
        return false;
    };
    // Check if the y positions of the player missile and the enemy missile with offset overlap
    if (myMissile.y != myEnemyMissile[enemy_missile_index].y)
    {
        return false;
    };

    // Check if the x positions of the missiles overlap
    if (myMissile.x + SIZE_MISSILE_BITMAP_X <= myEnemyMissile[enemy_missile_index].x)
    {
        return false;
    };

    // If all conditions are met, return true
    return true;
}
bool enemy_missile_player_ship_collision(uint8_t enemy_missile_index)
{
    // Check if the ship and the enemy missile are both visible
    if (myShip.ship.visible != WHITE || myEnemyMissile[enemy_missile_index].visible != WHITE)
    {
        return false;
    };
    // Check if the y positions of the ship and the enemy missile with offset overlap
    if (myShip.ship.y != myEnemyMissile[enemy_missile_index].y - SHIP_Y_OFFSET_FOR_MISSILES)
    {
        return false;
    };

    // Check if the x positions of the ship and the enemy missile overlap
    if (myShip.ship.x + SIZE_BITMAP_SHIP_X <= myEnemyMissile[enemy_missile_index].x)
    {
        return false;
    };

    // If all conditions are met, return true
    return true;
}