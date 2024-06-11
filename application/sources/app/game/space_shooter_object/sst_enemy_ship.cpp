#include "sst_ship.h"
#include "sst_enemy_brain.h"

sst_EnemyShip_t myEnemyShip;

/**
 * @brief Initializes the enemy ship.
 *
 * @details This function sets the initial values for the enemy ship's position, visibility, action image,
 * health, and number of missiles.
 *
 * @param None
 * @return None
 */
void sst_enemy_ship_init()
{
    APP_DBG_SIG("Enemy ship init\n");
    myEnemyShip.ship.visible = BLACK;
    myEnemyShip.ship.x = SHIP_X_COORDINATE;
    myEnemyShip.ship.y = SHIP_Y_COORDINATE;
    myEnemyShip.ship.action_image = rand() % 3 + 1;
    myEnemyShip.health = SHIP_LIFE;
    APP_DBG_SIG("Enemy ship health %d\n", myEnemyShip.health);
}

/**
 * @brief Initializes the enemy ship for takeoff.
 *
 * @details This function sets the initial values for the enemy ship's health, number of missiles, position, visibility, action image, and action.
 * 
 * @param None
 * @return None
 */
void sst_enemy_ship_takeoff()
{
    APP_DBG_SIG("Enemy ship takeoff\n");

    // Set enemy ship health and number of missiles
    myEnemyShip.health = SHIP_LIFE + myShip.fly_speed;
    total_health = myEnemyShip.health;
    APP_DBG_SIG("Enemy ship health %d\n", myEnemyShip.health);

    // Set enemy ship position
    myEnemyShip.ship.x = 150;
    myEnemyShip.ship.y = 20;

    // Set enemy ship visibility and action image
    myEnemyShip.ship.visible = WHITE;
}

/**
 * @brief Adjusts the flight of the enemy ship.
 *
 * @details This function is responsible for adjusting the flight of the enemy ship based on its visibility and action image.
 * If the ship's x position is greater than 100, it moves the ship to the left by 2 units. If the action image is 1, it calls the
 * randomize_enemy_ship_control function to determine the ship's next action.
 *
 * @param None
 * @return None
 */
void sst_enemy_ship_flight()
{
    // Check if the enemy ship is visible
    if (myEnemyShip.ship.visible != WHITE)
    {
        return; // If not visible, return and do nothing
    }

    // Adjust the ship's position based on conditions
    if (myEnemyShip.ship.x > 100)
    {
        // Fly enemy ship in range
        myEnemyShip.ship.x -= 2;
    }
    else
    {
        // Call the randomize_enemy_ship_control function to determine the ship's next action
        if (myShip.score > 800)
        {
            sst_ship_action = sst_better_strategy_based_enemy_control();
        }
        else
        {
            sst_ship_action = sst_better_randomize_enemy_control();
        }
    }

    // Increment the action image of the ship
    myEnemyShip.ship.action_image++;

    // Reset the action image if it reaches 4
    if (myEnemyShip.ship.action_image == 4)
    {
        myEnemyShip.ship.action_image = 1;
    }
}
void sst_enemy_ship_health_control()
{
    // Check if the health of the enemy ship is less than or equal to 0
    if (myEnemyShip.health <= 0)
    {
        // Make the enemy ship invisible
        myEnemyShip.ship.visible = BLACK;

        // Send message with points value data for player ship
        task_post_common_msg(SST_PLAYER_SHIP_TASK_ID, SST_SCORE_UPDATE_SIG, (uint8_t *) &myEnemyShip.enemy_ship_score, sizeof(myEnemyShip.enemy_ship_score));

        // Reset the enemy ship and enemy missile tasks
        task_post_pure_msg(SST_ENEMY_SHIP_TASK_ID, SST_ENEMY_SHIP_RESET_SIG);
        task_post_pure_msg(SST_ENEMY_MISSILE_TASK_ID, SST_ENEMY_MISSILE_RESET_SIG);

        // Print debug message
        APP_DBG_SIG("Enemy ship dead\n");

        // Change the game stage to GAME_STAGE_TERRAIN
        task_post_pure_msg(SST_TERRAIN_TASK_ID, SST_TERRAIN_INIT_SIG);
        sst_game_stage = GAME_STAGE_TERRAIN;

        // Return from the function
        return;
    }
}

/**
 * @brief Moves the enemy ship up or down based on the enemy ship action.
 *
 * @details This function is responsible for moving the enemy ship up or down based on the enemy ship action. 
 * If the enemy ship action is MOVE_UP, it moves the enemy ship up.
 * If the enemy ship action is MOVE_DOWN, it moves the enemy ship down.
 *
 * @param None
 * @return None
 */
void sst_enemy_ship_move()
{
    // Move the ship up if it is visible and the sst_ship_action is MOVE_UP
    if (myEnemyShip.ship.y > 0 && sst_ship_action == MOVE_UP)
    {
        // Print debug message
        APP_DBG_SIG("Enemy ship move up\n");

        // Update the ship's y position
        myEnemyShip.ship.y -= SHIP_Y_STEP;
    }

    // Move the ship down if it is visible and the sst_ship_action is MOVE_DOWN
    // if (myEnemyShip.ship.y < LCD_HEIGHT - SHIP_Y_STEP && sst_ship_action == MOVE_DOWN)
    // {
    //     // Print debug message
    //     APP_DBG_SIG("Enemy ship move down\n");

    //     // Update the ship's y position
    //     myEnemyShip.ship.y += SHIP_Y_STEP;
    // }

    if (myEnemyShip.ship.y < 40 && sst_ship_action == MOVE_DOWN)
    {
        // Print debug message
        APP_DBG_SIG("Enemy ship move down\n");

        // Update the ship's y position
        myEnemyShip.ship.y += SHIP_Y_STEP;
    }
}

/**
 * @brief Fires a missile from the enemy ship.
 *
 * @details This function checks if the ship action is set to FIRE and if the enemy ship has any missiles remaining.
 * If both conditions are met, a message is sent to fire a missile and the number of missiles is decremented by one.
 *
 * @param None
 * @return None
 */
void sst_enemy_ship_fire()
{
    // Check if the ship action is set to FIRE and if the enemy ship has any missiles remaining
    if (sst_ship_action == FIRE)
    {
        // Send a message to fire a missile
        APP_DBG_SIG("Enemy ship fire missile\n");
        task_post_pure_msg(SST_ENEMY_MISSILE_TASK_ID, SST_ENEMY_MISSILE_FIRE_SIG);
    }
}

/**
 * @brief Resets the enemy ship to its initial state.
 *
 * @details This function resets the enemy ship's position, visibility, action image, number of missiles, and health to their initial values.
 *
 * @param None
 * @return None
 */
void sst_enemy_ship_reset()
{
    APP_DBG_SIG("Enemy ship reset\n");
    myEnemyShip.ship.visible = BLACK;
    myEnemyShip.ship.x = 0;
    myEnemyShip.ship.y = 0;
    myEnemyShip.ship.action_image = rand() % 3 + 1;
    myEnemyShip.health = SHIP_LIFE;
    APP_DBG_SIG("Enemy ship health %d\n", myEnemyShip.health);
}

void sst_enemy_ship_handler(ak_msg_t *msg)
{
    switch (msg->sig)
    {
    case SST_ENEMY_SHIP_INIT_SIG:
        sst_enemy_ship_init();
        break;
    case SST_ENEMY_SHIP_TAKEOFF_SIG:
        sst_enemy_ship_takeoff();
        break;
    case SST_ENEMY_SHIP_FLIGHT_SIG:
        sst_enemy_ship_flight();
        sst_enemy_ship_health_control();
        break;
    case SST_ENEMY_SHIP_MOVE_SIG:
        sst_enemy_ship_move();
        break;
    case SST_ENEMY_SHIP_FIRE_SIG:
        sst_enemy_ship_fire();
        break;
    case SST_ENEMY_SHIP_RESET_SIG:
        sst_enemy_ship_reset();
        break;
    default:
        break;
    }
}
// NON-VOID FUNCTIONS IMPLEMENTATION ----------------------------------------------------------
// NON-PREFIXED FUNCTIONS IMPLEMENTATION ------------------------------------------------------

// TODO: add this function: @brief Retreats the enemy ship when "x" time have passed
void enemy_ship_retreat()
{
    APP_DBG_SIG("Enemy ship retreat\n");

    // Check if enemy ship is within the screen boundaries
    if (myEnemyShip.ship.x + SIZE_BITMAP_SHIP_X < LCD_WIDTH)
    {
        // Move enemy ship towards the right side of the screen
        myEnemyShip.ship.x++;
    }
    else
    {
        // Make enemy ship invisible
        myEnemyShip.ship.visible = BLACK;
    }
}