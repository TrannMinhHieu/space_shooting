#include "sst_explosion.h"

Explosion myExplosion;

/**
 * @brief Initialize the explosion with default values.
 *
 * @param None
 * @return None
 */
void explosion_init()
{
    // Print a debug message indicating that the explosion is being initialized.
    APP_DBG_SIG("Explosion init\n");

    // Set the properties of myExplosion object
    myExplosion.visible = BLACK;
    myExplosion.x = 0;
    myExplosion.y = 0;
    myExplosion.action_image = 1;
}

/**
 * @brief Update the action image of the explosion.
 * 
 * @param None
 * @return None 
 */
void explosion_explode()
{
    if (myExplosion.visible != WHITE)
    {
        return;
    }
    APP_DBG_SIG("Explosion explode\n");
    // If the explosion is visible, update the action image
    myExplosion.action_image++;
    // If the action image reaches 4, reset it and make the explosion invisible
    if (myExplosion.action_image == 4)
    {
        myExplosion.action_image = 1;
        myExplosion.visible = BLACK;
    }
}

/**
 * @brief Reset the explosion.
 *
 * @param None
 * @return None
*/
void explosion_reset()
{
    APP_DBG_SIG("Explosion reset\n");
    myExplosion.visible = BLACK;
    myExplosion.x = 0;
    myExplosion.y = 0;
}

/**
 * @brief Handler for the explosion task.
 * 
 * @param msg 
 * @return None
 */
void sst_explosion_handler(ak_msg_t *msg)
{
    switch (msg->sig)
    {
    case SST_EXPLOSION_INIT_SIG:
        explosion_init();
        break;
    case SST_EXPLPOSION_EXPLODE_SIG:
        explosion_explode();
        break;
    case SST_EXPLOSION_RESET_SIG:
        explosion_reset();
        break;
    default:
        break;
    }
}