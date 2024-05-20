#include "sst_terrain.h"
#include <vector>

using namespace std;

bool is_terrain_out_of_screen(int terrain_index);
uint32_t round_to_tens_of_integer(uint32_t shipYCoordinate);
void terrain_end();
void terrain_collision(uint8_t terrain_index);

/**
 * @brief Define the terrain vector.
 *
 * @todo Add perlin noise
 */
std::vector<TerrainCoordinates> v_terrain;

const int TerrainCoordinates::terrain_score = 5;

/**
 * @brief Initialize the terrain coordinates.
 */
TerrainCoordinates::TerrainCoordinates()
{
    this->x = 140;
    // TODO: intergrate perlin noise for smoother terrain
    this->y = (rand() % 30) + 30;
}
/**
 * @brief Initialize the terrain coordinates.
 *
 * @param x, y
 */
TerrainCoordinates::TerrainCoordinates(int x, int y)
{
    this->x = x;
    this->y = y;
}
/**
 * @brief Move the terrain.
 *
 * @note The terrain moves from right to left.
 * Depending on the ship's speed, the terrain moves faster or slower.
 */
void TerrainCoordinates::terrainMover()
{
    this->x = this->x - myShip.fly_speed;
}

/**
 * @brief Initialize the terrain.
 *
 * @note Pre-added two terrain coordinates for smooth terrain initialization.
 */
void terrain_init()
{
    APP_DBG_SIG("Terrain init\n");
    v_terrain.push_back(TerrainCoordinates(140, 60));
    v_terrain.push_back(TerrainCoordinates(160, 50));
}

/**
 * @brief Generate a new terrain.
 */
void terrain_generate()
{
    v_terrain.push_back(TerrainCoordinates());
    APP_DBG_SIG("Terrain size %d\n", v_terrain.size());
}

static int generated = 0;
static int terrainLength = 20;
/**
 * @brief Update the terrain.
 *
 * @details This function updates the terrain coordinates if the terrain is less than the pre-calculated length.
 * The newly generated terrain coordinates are added to the vector if the previous coordinates pass desinated position
 * and the terrain vector size is less than pre-defined TERRAIN_MAX_LENGTH.
 * If the terrain is out of the screen, the coordinates are removed from the vector.
 * If the terrain reaches the pre-calculated length, end the terrain generation.
 *
 * @param None
 * @return None
 */
void terrain_update()
{
    static int x_coord_tracker;
    for (uint8_t i = 0; i < v_terrain.size(); i++)
    {
        // Move terrain coordinate if generated terrains is less than terrainLength
        if (generated < terrainLength)
        {
            v_terrain[i].terrainMover();
        }

        // Update x_coord_tracker with the x-coordinate of the last terrain coordinate
        x_coord_tracker = v_terrain.back().x;

        // Check for terrain collisions
        terrain_collision(i);

        // End terrain generation if generated terrains is equal to terrainLength
        if (generated == terrainLength)
        {
            terrain_end();
            break;
        }
        // Generate new terrain coordinate if last terrain coordinate is within screen width and v_terrain size is less than TERRAIN_MAX_LENGTH
        else if (x_coord_tracker < LCD_WIDTH + 2 && v_terrain.size() < TERRAIN_MAX_LENGTH)
        {
            terrain_generate();
            generated++;
            APP_DBG_SIG("Generated %d\n", generated);
            break;
        }

        // Remove terrain coordinate if out of screen and update ship's score
        if (is_terrain_out_of_screen(i))
        {
            v_terrain.erase(v_terrain.begin() + i);
            // Send message to update score
            task_post_common_msg(SST_PLAYER_SHIP_TASK_ID, SST_SCORE_UPDATE_SIG, (uint8_t *) &v_terrain[i].terrain_score, sizeof(v_terrain[i].terrain_score));
            APP_DBG_SIG("Terrain size %d\n", v_terrain.size());
        }
    }
}

/**
 * @brief Check if the terrain is colliding with the ship or the missile.
 *
 * @details This function first checks if the terrain is within a certain range
 * of the ship to avoid unnecessary calculations. If the terrain is within the
 * range, it then checks if the ship and the terrain are colliding. If they are,
 * it makes the ship invisible and spawns an explosion at the ship's position. It
 * also sends a message to exit the game.
 *
 * Next, it checks if the missile and the terrain are colliding. If they are, it
 * makes the missile invisible and spawns an explosion at the missile's position.
 * After that, it resets the missile's position.
 *
 * @param terrain_index The index of the terrain coordinate in the vector.
 * @return None
 */
void terrain_collision(uint8_t terrain_index)
{
    // Check if the terrain is within a certain range of the ship
    if (v_terrain[terrain_index].x < 10)
    {
        return;
    }
    else
    {
        // Check if the ship and the terrain are colliding
        if ((int)myShip.ship.y + SIZE_BITMAP_SHIP_Y >= v_terrain[terrain_index].y && (int)myShip.ship.x + SIZE_BITMAP_SHIP_X >= v_terrain[terrain_index].x)
        {
            // Make the ship invisible
            myShip.ship.visible = BLACK;

            // Spawn an explosion at the ship's position
            myExplosion.visible = WHITE;
            myExplosion.x = myShip.ship.x;
            myExplosion.y = myShip.ship.y;

            // Print debug message
            APP_DBG_SIG("Ship hit terrain\n");
            APP_DBG_SIG("at: terrain[%d] %d, %d\n", terrain_index, v_terrain[terrain_index].x, v_terrain[terrain_index].y);

            // Exit the game
            task_post_pure_msg(SST_GAMEPLAY_TASK_ID, GAME_EXIT);
        }

        // Check if the missile and the terrain are colliding
        if ((int)myMissile.y + SIZE_MISSILE_BITMAP_Y >= v_terrain[terrain_index].y && (int)myMissile.x + SIZE_MISSILE_BITMAP_Y - 3 >= v_terrain[terrain_index].x)
        {
            // Make the missile invisible
            myMissile.visible = BLACK;

            // Spawn an explosion at the missile's position
            myExplosion.visible = WHITE;
            myExplosion.x = myMissile.x;
            myExplosion.y = myMissile.y;

            // Reset the missile's position
            myMissile.x = 0;

            // Terrain interaction with missile
            if (v_terrain[terrain_index].y < 50)
            {
                v_terrain[terrain_index].y += 10;
            }
        }
    }
}

/**
 * @brief Check if the game should end and reset the terrain if needed.
 *
 * End the terrain generation process if the terrain vector size is less than or equal to 1.
 * Generates initial terrain coordinates if not done yet.
 * Moves existing terrain coordinates and handles collisions with the terrain.
 * If terrain coordinates are out of screen, remove them from the vector and update the player's score.
 *
 * @param None
 * @return None
 */
void terrain_end()
{
    // Flag to check if the terrain end coordinate generation has been done
    static bool done = false;

    // Check if the terrain end coordinate generation has not been done
    if (!done)
    {
        // Add the initial terrain coordinates
        v_terrain.push_back(TerrainCoordinates(155, 50));
        v_terrain.push_back(TerrainCoordinates(180, 60));

        // Set the done flag to true
        done = true;
    }

    // Check if the terrain vector size is less than or equal to 1
    if (v_terrain.size() <= 1)
    {
        // Display a debug message
        APP_DBG_SIG("Terrain end\n");

        // Reset the done flag
        done = false;

        // Round the ship's y position to the nearest tens of integer
        myShip.ship.y = round_to_tens_of_integer(myShip.ship.y);

        // Soft terrain reset
        v_terrain.clear();
        generated = 0;
        terrainLength = terrainLength * 2;

        // Post a message to spawn asteroids
        task_post_pure_msg(SST_ASTEROID_TASK_ID, SST_ASTEROID_SPAWN_SIG);

        // Set the game stage to the asteroid field
        sst_game_stage = GAME_STAGE_ASTEROID_FEILD;
    }

    // Iterate over the terrain vector
    for (uint8_t i = 0; i < v_terrain.size(); i++)
    {
        // Move the terrain
        v_terrain[i].terrainMover();

        // Check if there is a collision between the terrain and the ship or the missile
        terrain_collision(i);

        // Check if the terrain is out of the screen
        if (is_terrain_out_of_screen(i))
        {
            // Remove the terrain from the vector
            v_terrain.erase(v_terrain.begin() + i);

            // Increment the ship's score by 5
            myShip.score += 5;

            // Display the score and terrain size
            APP_DBG_SIG("Score %d\n", myShip.score);
            APP_DBG_SIG("Terrain size %d\n", v_terrain.size());
        }
    }
}

/**
 * @brief Reset the terrain.
 *
 * @details This function clears the terrain vector, sets the generated variable to 0, and doubles the terrainLength variable.
 *
 * @param None
 * @return None
 */
void terrain_reset()
{
    // Print debug message
    APP_DBG_SIG("Terrain reset\n");

    // Clear the terrain vector
    v_terrain.clear();

    // Set the generated variable to 0
    generated = 0;

    // Reset the terrainLength variable
    terrainLength = 20;
}

/**
 * @brief Handle the terrain messages.
 *
 * @details This function handles the terrain messages based on the message signature.
 * It initializes the terrain, updates the terrain, and resets the terrain.
 *
 * @param msg Pointer to the message
 * @return None
 */
void sst_terrain_handler(ak_msg_t *msg)
{
    // Check the message signature
    switch (msg->sig)
    {
    // Initialize the terrain
    case SST_TERRAIN_INIT_SIG:
        terrain_init();
        APP_DBG_SIG("Terrain length: %d\n", terrainLength);
        break;

    // Update the terrain
    case SST_TERRAIN_UPDATE_SIG:
        terrain_update();
        break;

    // Reset the terrain
    case SST_TERRAIN_RESET_SIG:
        terrain_reset();
        break;

    // Do nothing for other message signatures
    default:
        break;
    }
}
// Non-void functions implementation ----------------------------------------------------------
/**
 * @brief Terrain ship collision.
 *
 * @param terrain_index
 * @return true if the ship and the terrain are colliding, false otherwise
 */
bool terrain_ship_collision(int terrain_index)
{
    if (v_terrain[terrain_index].y < (int)myShip.ship.y)
    {
        return true;
    }

    return false;
}
/**
 * @brief Check if the terrain is out of the screen.
 *
 * @param terrain_index
 * @return true if the terrain is out of the screen, false otherwise
 */
bool is_terrain_out_of_screen(int terrain_index)
{
    if (v_terrain[terrain_index].x < -15)
    {
        return true;
    }
    return false;
}
/**
 * @brief Round to the nearest tens of integer
 *
 * @param shipYCoordinate
 * @return uint32_t the nearest tens of integer
 */
uint32_t round_to_tens_of_integer(uint32_t shipYCoordinate)
{
    uint32_t shipYRound = shipYCoordinate % 10;
    if (shipYRound > 5)
    {
        return shipYCoordinate - shipYRound + 10;
    }
    else
    {
        return shipYCoordinate - shipYRound;
    }
}