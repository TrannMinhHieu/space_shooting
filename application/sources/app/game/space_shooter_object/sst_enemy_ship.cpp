#include "sst_ship.h"
#include "enemy_brain.h"

EnemyShip myEnemyShip;

/**
 * @brief Initializes the enemy ship.
 *
 * @details This function sets the initial values for the enemy ship's position, visibility, action image,
 * health, and number of missiles.
 *
 * @param: None
 * @return: None
 */
void enemy_ship_init()
{
    APP_DBG_SIG("Enemy ship init\n");
    myEnemyShip.ship.visible = BLACK;
    myEnemyShip.ship.x = SHIP_X_COORDINATE;
    myEnemyShip.ship.y = SHIP_Y_COORDINATE;
    myEnemyShip.ship.action_image = rand() % 3 + 1;
    myEnemyShip.health = SHIP_LIFE;
    myEnemyShip.num_missiles = MAX_NUM_OF_ENEMY_MISSILE;
    APP_DBG_SIG("Enemy ship health %d\n", myEnemyShip.health);
    APP_DBG_SIG("Enemy max missile %d\n", myEnemyShip.num_missiles);
}

/**
 * @brief Initializes the enemy ship for takeoff.
 *
 * @details This function sets the initial values for the enemy ship's position, visibility, action image, and action.
 * @param: None
 * @return: None
 */
void enemy_ship_takeoff()
{
    APP_DBG_SIG("Enemy ship takeoff\n");

    // Set enemy ship position
    myEnemyShip.ship.x = 150;
    myEnemyShip.ship.y = 20;

    // Set enemy ship visibility and action image
    myEnemyShip.ship.visible = WHITE;
    myEnemyShip.ship.action_image = 1;
}

// TODO: add this function. @brief Retreats the enemy ship when "x" time have passed
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
void enemy_ship_flight()
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
            ship_action = strategy_based_enemy_control();
        }
        else
        {
            ship_action = better_randomize_enemy_control();
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
void enemy_ship_health_control()
{
    // Check if the health of the enemy ship is less than or equal to 0
    if (myEnemyShip.health <= 0)
    {
        // Make the enemy ship invisible
        myEnemyShip.ship.visible = BLACK;

        // TODO: Send message with points value data for player ship
        // Increase the player's score by 100
        myShip.score += 100;

        // Reset the enemy ship and enemy missile tasks
        task_post_pure_msg(ENEMY_SHIP_TASK_ID, ENEMY_SHIP_RESET_SIG);
        task_post_pure_msg(ENEMY_MISSILE_TASK_ID, ENEMY_MISSILE_RESET_SIG);

        // Print debug message
        APP_DBG_SIG("Enemy ship dead\n");

        // Change the game stage to GAME_STAGE_ASTEROID_FEILD
        task_post_pure_msg(ASTEROID_TASK_ID, ASTEROID_SPAWN_SIG);
        game_stage = GAME_STAGE_ASTEROID_FEILD;

        // Return from the function
        return;
    }
}

/**
 * @brief Moves the enemy ship up or down based on its visibility and ship action.
 *
 * @details This function checks if the enemy ship is visible and its x position is less than 100.
 * If the ship is visible and the ship action is MOVE_UP, the ship is moved up by SHIP_Y_STEP units.
 * If the ship is visible and the ship action is MOVE_DOWN, the ship is moved down by SHIP_Y_STEP units.
 *
 * @param None
 * @return None
 */
void enemy_ship_move()
{
    // Check if the enemy ship is visible and its x position is less than 100
    if (myEnemyShip.ship.visible != WHITE || myEnemyShip.ship.x > 100)
    {
        return;
    }

    // Move the ship up if it is visible and the ship_action is MOVE_UP
    if (myEnemyShip.ship.y > 0 && ship_action == MOVE_UP)
    {
        // Print debug message
        APP_DBG_SIG("Enemy ship move up\n");

        // Update the ship's y position
        myEnemyShip.ship.y -= SHIP_Y_STEP;
    }

    // Move the ship down if it is visible and the ship_action is MOVE_DOWN
    if (myEnemyShip.ship.y < LCD_HEIGHT - SHIP_Y_STEP && ship_action == MOVE_DOWN)
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
void enemy_ship_fire()
{
    // Check if the ship action is set to FIRE and if the enemy ship has any missiles remaining
    if (myEnemyShip.num_missiles > 0 && ship_action == FIRE)
    {
        // Decrement the number of missiles by one
        myEnemyShip.num_missiles--;

        // Send a message to fire a missile
        APP_DBG_SIG("Enemy ship fire missile\n");
        task_post_pure_msg(ENEMY_MISSILE_TASK_ID, ENEMY_MISSILE_FIRE_SIG);
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
void enemy_ship_reset()
{
    APP_DBG_SIG("Enemy ship reset\n");
    myEnemyShip.ship.visible = BLACK;
    myEnemyShip.ship.x = 0;
    myEnemyShip.ship.y = 0;
    myEnemyShip.ship.action_image = rand() % 3 + 1;
    myEnemyShip.health = SHIP_LIFE + (myShip.fly_speed);
    myEnemyShip.num_missiles = MAX_NUM_OF_ENEMY_MISSILE + (myShip.fly_speed);
    APP_DBG_SIG("Enemy ship health %d\n", myEnemyShip.health);
    APP_DBG_SIG("Enemy max missile %d\n", myEnemyShip.num_missiles);
}

void enemy_ship_handler(ak_msg_t *msg)
{
    switch (msg->sig)
    {
    case ENEMY_SHIP_INIT_SIG:
        enemy_ship_init();
        break;
    case ENEMY_SHIP_TAKEOFF_SIG:
        enemy_ship_takeoff();
        break;
    case ENEMY_SHIP_FLIGHT_SIG:
        enemy_ship_flight();
        enemy_ship_health_control();
        break;
    case ENEMY_SHIP_MOVE_SIG:
        enemy_ship_move();
        break;
    case ENEMY_SHIP_FIRE_SIG:
        enemy_ship_fire();
        break;
    case ENEMY_SHIP_RESET_SIG:
        enemy_ship_reset();
        break;
    default:
        break;
    }
}