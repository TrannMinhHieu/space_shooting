#include "asteroid.h"

Asteroid myAsteroid[NUM_ASTEROIDS];
uint16_t asteroid_count = 0;

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
        // Assign random x-coordinate
        myAsteroid[i].x = (rand() % 39) + 130;

        // Assign corresponding y-coordinate from asteroidYCoordinates
        myAsteroid[i].y = asteroidYCoordinates[i];

        // Set default values for visibility and action image
        myAsteroid[i].visible = WHITE;
        myAsteroid[i].action_image = 1;
    }
}

/**
 * Checks if any of the asteroids in the `myAsteroid` array have moved off the screen by checking their x-coordinates.
 *
 * @param asteroid_index The index of the asteroid in the `myAsteroid` array.
 * @return A boolean value indicating whether any of the asteroids have moved off the screen.
 */
bool is_asteroid_out_of_screen(uint8_t asteroid_index)
{
    // Check if the x-coordinate plus the width of the current asteroid is less than 0.
    if (myAsteroid[asteroid_index].x + SIZE_BITMAP_ASTEROIDS_X < 0)
    {
        // If an asteroid's x-coordinate is less than 0, return true to indicate that it has moved off the screen.
        return true;
    }
    // If none of the asteroids have moved off the screen, return false.
    return false;
}

/**
 * @brief Update the position and action image of each asteroid in the `myAsteroid` array.
 *
 * This function updates the position with default flight speed, and action image of each asteroid in the `myAsteroid` array.
 * It also checks if an asteroid has moved off the screen.
 *
 * @param None
 * @return None
 */
// TODO: increase tempo for faster asteroid movement
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
 * Checks if a missile has collided with an asteroid.
 *
 * @param asteroid_index The index of the asteroid in the `myAsteroid` array.
 * @return True if a collision has occurred, False otherwise.
 */
bool asteroid_missile_collision(uint8_t asteroid_index)
{
    // Check if the missile is visible and its x-coordinate plus its width is greater than the x-coordinate of the asteroid.
    // Check if the missile's y-coordinate minus 2 is equal to the y-coordinate of the asteroid.
    if (myMissile.visible == WHITE
        && (int32_t)(myMissile.x + SIZE_MISSILE_BITMAP_X) > myAsteroid[asteroid_index].x
        && (int32_t)(myMissile.y - MISSILE_Y_OFFSET_FOR_ASTEROID) == myAsteroid[asteroid_index].y)
    {
        return true; // Collision occurred
    }
    return false; // No collision occurred
}

/**
 * Checks if the ship has collided with an asteroid.
 *
 * @param asteroid_index The index of the asteroid in the myAsteroid array.
 * @return true if a collision between the ship and the asteroid has occurred, false otherwise.
 */
bool asteroid_ship_collision(uint8_t asteroid_index)
{
    // Check if the ship is visible and its x-coordinate plus its width is greater than the x-coordinate of the asteroid
    // Also, check if the ship's y-coordinate is equal to the y-coordinate of the asteroid minus 3
    if (myShip.ship.visible == WHITE
        && (int32_t)(myShip.ship.x + SIZE_BITMAP_SHIP_X) > myAsteroid[asteroid_index].x
        && (int32_t)(myShip.ship.y) == myAsteroid[asteroid_index].y - SHIP_Y_OFFSET_FOR_ASTEROID)
    {
        return true; // Collision occurred
    }
    return false; // No collision occurred
}

/**
 * @brief Handle the collision of an asteroid with a missile or a ship.
 *
 * @param None
 * @return None
 */
void asteroid_hit()
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
            myMissile.visible = BLACK;
            myMissile.x = 0;
            // Send message to increment score
            task_post_pure_msg(SHIP_PLAYER_TASK_ID, MISSILE_DESTROY_SIG);

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
                task_post_pure_msg(GAMEPLAY_TASK_ID, GAME_EXIT);
            }
            else
            {
                // Send messages to handle ship being hit and explode the asteroid
                task_post_pure_msg(SHIP_PLAYER_TASK_ID, SHIP_HIT_SIG);
                task_post_pure_msg(EXPLOSION_TASK_ID, EXPLPOSION_EXPLODE_SIG);
            }
        }
    }
}

void asteroid_field_control()
{
    for (uint8_t i = 0; i < NUM_ASTEROIDS; i++)
    {
        if(asteroid_missile_collision(i))
        {
            asteroid_count++;
            APP_DBG_SIG("Number of asteroids destroyed: %d\n", asteroid_count);
        }
        if(asteroid_count >= 15) 
        {
            APP_DBG_SIG("Reset asteroids\n");
            task_post_pure_msg(ASTEROID_TASK_ID, ASTEROID_RESET_SIG);
            asteroid_count = 0;
            APP_DBG_SIG("Asteroid count = %d\n", asteroid_count);
            game_stage = GAME_STAGE_SHIP_FIGHT;
            task_post_pure_msg(SHIP_ENEMY_TASK_ID, SHIP_ENEMY_TAKEOFF_SIG);
            break;
        }
    }
}

/**
 * @brief Reset the asteroids.
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
        // myAsteroid[i].visible = BLACK;
        myAsteroid[i].visible = WHITE;

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
void asteroid_handler(ak_msg_t *msg)
{
    switch (msg->sig)
    {
    case ASTEROID_INIT_SIG:
        asteroid_init();
        break;
    case ASTEROID_FLIGHT_SIG:
        asteroid_flight();
        asteroid_field_control();
        break;
    case SHIP_HIT_SIG:
    case MISSILE_HIT_SIG:
        asteroid_hit();
        break;
    case ASTEROID_RESET_SIG:
        asteroid_reset();
        break;
    default:
        // Do nothing for unknown signals
        break;
    }
}