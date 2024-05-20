#include "sst_asteroid.h"

Asteroid_t myAsteroid[NUM_ASTEROIDS];
uint16_t asteroid_count = 0;

bool is_asteroid_out_of_screen(uint8_t asteroid_index);
bool asteroid_missile_collision(uint8_t asteroid_index);
bool asteroid_ship_collision(uint8_t asteroid_index);

/**
 * @brief Initialize the asteroids with random x-coordinates, predefined y-coordinates, and default values.
 *
 * This function initializes the `myAsteroid` array with random x-coordinates, predefined y-coordinates,
 * and default values for visibility and action image.
 *
 * @param None
 * @return None
 */
void asteroid_init()
{
    // Print debug message
    APP_DBG_SIG("Asteroid init\n");

    // Initialize asteroids
    for (uint8_t i = 0; i < NUM_ASTEROIDS; i++)
    {
        // Set default values for visibility
        myAsteroid[i].visible = WHITE;

        // Assign random x-coordinate
        myAsteroid[i].x = (rand() % 39) + 130;

        // Assign corresponding y-coordinate from asteroidYCoordinates
        myAsteroid[i].y = asteroidYCoordinates[i];

        // Set default action image
        myAsteroid[i].action_image = rand() % 3 + 1;
    }
}

/**
 * @brief Spawn asteroids.
 *
 * This function sets the visibility of each asteroid in the `myAsteroid` array to white, indicating that they are visible on the screen.
 *
 * @param None
 * @return None
 */
void asteroid_spawn()
{
    APP_DBG_SIG("Asteroid spawn\n");
    for (uint8_t i = 0; i < NUM_ASTEROIDS; i++) 
    {
        myAsteroid[i].visible = WHITE;
    }
}

/**
 * @brief Update the position and action image of each asteroid in the `myAsteroid` array.
 *
 * This function updates the position with player ship flight speed and action image of each asteroid in the `myAsteroid` array.
 * It also checks if an asteroid has moved off the screen and repositions it randomly within a specific range.
 *
 * @param None
 * @return None
 */
void asteroid_flight()
{
    for (uint8_t i = 0; i < NUM_ASTEROIDS; i++)
    {
        // Check if the asteroid is visible
        if (myAsteroid[i].visible == WHITE)
        {
            // Update the x-coordinate by subtracting the myShip.fly_speed
            myAsteroid[i].x -= myShip.fly_speed;

            // Increment the action image of the asteroid
            myAsteroid[i].action_image++;

            // Reset the action image to 1 if it reaches 4
            if (myAsteroid[i].action_image == 4)
            {
                myAsteroid[i].action_image = 1;
            }

            // Check if the asteroid has moved off the screen
            if (is_asteroid_out_of_screen(i))
            {
                APP_DBG_SIG("Asteroid out of range\n");

                // Reposition the asteroid randomly within a specific range
                myAsteroid[i].x = (rand() % 39) + 130;
            }
        }
    }
}

/**
 * @brief Handle the collision of an asteroid with a missile or a ship.
 *
 * This function checks if an asteroid has collided with a missile or a ship.
 * If a collision occurs, the corresponding explosion is displayed and the asteroid and missile are reset.
 *
 * @param None
 * @return None
 */
void asteroid_hit_handler()
{
    // Iterate through each asteroid in the myAsteroid array
    for (uint8_t i = 0; i < NUM_ASTEROIDS; i++)
    {
        // Check if asteroid is visible and hit by missile
        if (asteroid_missile_collision(i))
        {
            APP_DBG_SIG("Missile hit asteroid\n");
            APP_DBG_SIG("Asteroid no %d hit by missile\n", i);
            // Update explosion position with asteroid's coordinates
            myExplosion.visible = WHITE;
            myExplosion.x = myAsteroid[i].x;
            myExplosion.y = myAsteroid[i].y;

            // Missile visibility is set to black
            // Reset position of missile
            myMissile.visible = BLACK;
            myMissile.x = 0;

            // Send message with points value data for player ship
            task_post_common_msg(SST_PLAYER_SHIP_TASK_ID, SST_SCORE_UPDATE_SIG, (uint8_t *) &myAsteroid[i].asteroid_score, sizeof(myAsteroid[i].asteroid_score));

            // Move the asteroid to a new random position
            myAsteroid[i].x = (rand() % 39) + 130;
        }

        // Check if asteroid is visible and hit by ship
        if (asteroid_ship_collision(i))
        {
            APP_DBG_SIG("Ship hit asteroid\n");
            APP_DBG_SIG("Asteroid no %d hit by ship\n", i);
            // Update explosion position with ship's coordinates
            myExplosion.visible = WHITE;
            myExplosion.x = myShip.ship.x;
            myExplosion.y = myShip.ship.y;

            // Hide the ship
            myShip.ship.visible = BLACK;

            // If ship is hidden, exit the game
            if (myShip.ship.visible == BLACK)
            {
                task_post_pure_msg(SST_GAMEPLAY_TASK_ID, GAME_EXIT);
            }
            else
            {
                // Send messages to handle ship being hit and explode the asteroid
                task_post_pure_msg(SST_PLAYER_SHIP_TASK_ID, SST_SHIP_HIT_SIG);
                task_post_pure_msg(SST_EXPLOSION_TASK_ID, SST_EXPLPOSION_EXPLODE_SIG);
            }
        }
    }
}

/**
 * @brief Control the asteroid field.
 *
 * This function controls the asteroid field by checking for missile collisions with asteroids.
 * It keeps track of the number of asteroids destroyed and resets the asteroids when a certain threshold is reached.
 * It also updates the game stage and sends a message to the player ship task to initiate enemy takeoff.
 *
 * @param None
 * @return None
 */
void asteroid_field_control()
{
    // Iterate through each asteroid in the myAsteroid array
    for (uint8_t i = 0; i < NUM_ASTEROIDS; i++)
    {
        // Check if the asteroid has been destroyed by a missile collision
        if (asteroid_missile_collision(i))
        {
            // Increment the asteroid_count variable and print the number of asteroids destroyed
            asteroid_count++;
            APP_DBG_SIG("Number of asteroids destroyed: %d\n", asteroid_count);
        }

        // Check if the asteroid_count is equal to or greater than 15 (base), increased by 4 for each speed level
        if (asteroid_count >= 15 + ((myShip.fly_speed - 1) * 4))
        {
            // Reset all the asteroids
            APP_DBG_SIG("Reset asteroids\n");
            task_post_pure_msg(SST_ASTEROID_TASK_ID, SST_ASTEROID_RESET_SIG);

            // Reset the asteroid_count
            asteroid_count = 0;
            APP_DBG_SIG("Asteroid count = %d\n", asteroid_count);

            // Set the game stage to "SHIP_FIGHT"
            sst_game_stage = GAME_STAGE_SHIP_FIGHT;

            // Re-arm the enemy ship
            task_post_pure_msg(SST_ENEMY_MISSILE_TASK_ID, SST_ENEMY_MISSILE_INIT_SIG);
            // Trigger the enemy ship to take off
            task_post_pure_msg(SST_ENEMY_SHIP_TASK_ID, SST_ENEMY_SHIP_TAKEOFF_SIG);

            // Break out of the loop
            break;
        }
    }
}

/**
 * @brief Reset the asteroids.
 *
 * This function resets the asteroids by setting their visibility to white, assigning new random x-coordinates within the range of 130 to 168,
 * and assigning new random action images to each asteroid in the myAsteroid array.
 *
 * @param None
 * @return None
 */
void asteroid_reset()
{
    // Print a debug message indicating that the asteroids are being reset.
    APP_DBG_SIG("Asteroid reset\n");

    // Iterate through each asteroid in the myAsteroid array.
    for (uint8_t i = 0; i < NUM_ASTEROIDS; i++)
    {
        // Set the visibility of the asteroid to black.
        myAsteroid[i].visible = BLACK;

        // Assign a new random x-coordinate within the range of 130 to 168.
        myAsteroid[i].x = (rand() % 39) + 130;

        // Assign a new random action image to the asteroid.
        myAsteroid[i].action_image = rand() % 3 + 1;
    }
}

/**
 * @brief Message handler for the asteroid task.
 *
 * @param msg The message to handle.
 * @return None
 */
void sst_asteroid_handler(ak_msg_t* msg)
{
    switch (msg->sig)
    {
    case SST_ASTEROID_INIT_SIG:
        asteroid_init();
        break;
    case SST_ASTEROID_SPAWN_SIG:
        asteroid_spawn();
        break;
    case SST_ASTEROID_FLIGHT_SIG:
        asteroid_flight();
        asteroid_field_control();
        break;
    case SST_SHIP_HIT_SIG:
    case SST_MISSILE_HIT_SIG:
        asteroid_hit_handler();
        break;
    case SST_ASTEROID_RESET_SIG:
        asteroid_reset();
        break;
    default:
        // Do nothing for unknown signals
        break;
    }
}

// Non-void functions implementation ----------------------------------------------------------
/**
 * Checks if any of the asteroids in the `myAsteroid` array have moved off the screen by checking their x-coordinates.
 *
 * @param asteroid_index The index of the asteroid in the `myAsteroid` array.
 * @return A boolean value indicating whether any of the asteroids have moved off the screen.
 */
bool is_asteroid_out_of_screen(uint8_t asteroid_index)
{
    // Check if the x-coordinate plus the width of the current asteroid is less than SCREEN_LEFT_BOUNDARY (0).
    if (myAsteroid[asteroid_index].x + SIZE_BITMAP_ASTEROIDS_X < SCREEN_LEFT_BOUNDARY)
    {
        // If an asteroid's x-coordinate is less than 0, return true to indicate that it has moved off the screen.
        return true;
    }
    // If none of the asteroids have moved off the screen, return false.
    return false;
}
/**
 * Checks if a missile has collided with an asteroid.
 *
 * @param asteroid_index The index of the asteroid in the `myAsteroid` array.
 * @return True if a collision has occurred, False otherwise.
 */
bool asteroid_missile_collision(uint8_t asteroid_index)
{
    // Check if the missile or the asteroid is not visible
    if (myMissile.visible != WHITE || myAsteroid[asteroid_index].visible != WHITE)
    {
        return false;
    }

    // Check if the missile and asteroid have the same y-coordinate
    if (myMissile.y - MISSILE_Y_OFFSET_FOR_ASTEROID != (uint32_t)myAsteroid[asteroid_index].y)
    {
        return false;
    }

    // Check if the missile and asteroid have the same x-coordinate
    if (myMissile.x + SIZE_BITMAP_MISSILE_X <= (uint32_t)myAsteroid[asteroid_index].x)
    {
        return false;
    }

    // Collision occurred
    return true;
}

/**
 * Checks if the ship has collided with an asteroid.
 *
 * @param asteroid_index The index of the asteroid in the myAsteroid array.
 * @return true if a collision between the ship and the asteroid has occurred, false otherwise.
 */
bool asteroid_ship_collision(uint8_t asteroid_index)
{
    // Check if the ship or the asteroid is not visible
    if (myShip.ship.visible != WHITE || myAsteroid[asteroid_index].visible != WHITE)
    {
        return false;
    }

    // Check if the ship and asteroid have the same y-coordinate
    if (myShip.ship.y + SHIP_Y_OFFSET_FOR_ASTEROID != (uint32_t)myAsteroid[asteroid_index].y)
    {
        return false;
    }

    // Check if the ship and asteroid have the same x-coordinate
    if (myShip.ship.x + SIZE_BITMAP_SHIP_X <= (uint32_t)myAsteroid[asteroid_index].x)
    {
        return false;
    }

    // Collision occurred
    return true;
}
