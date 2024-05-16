#include "sst_ship.h"

PlayerShip myShip;

/**
 * @brief Initialize the ship with default values.
 *
 * @param None
 * @return None
 */
void player_ship_init()
{
    APP_DBG_SIG("Ship init\n");
    myShip.ship.x = SHIP_X_COORDINATE;
    myShip.ship.y = SHIP_Y_COORDINATE;
    myShip.ship.visible = WHITE;
    myShip.ship.action_image = 1;
    myShip.score = 0;
    myShip.fly_speed = 1;
}

/**
 * @brief Display the ship animation.
 *
 * @param None
 * @return None
 */
void player_ship_flight()
{
    if((int32_t)myShip.ship.y < 0)
    {
        myShip.ship.y = 0;
    }
    // Cycle through the ship animation
    myShip.ship.action_image++;
    if (myShip.ship.action_image == 4)
    {
        myShip.ship.action_image = 1;
    }

    if (myShip.score % 200 == 0 && myShip.fly_speed < 8 && myShip.score > 0)
    {
        // Increase the ship speed as the score increases
        myShip.fly_speed++;
        APP_DBG_SIG("Ship fly speed %d\n", myShip.fly_speed);
        myShip.score += 10; // break point
    }
}

/**
 * @brief Fire a missile.
 *
 * @param None
 * @return None
 */
void player_ship_fire()
{
    // Send message to fire a missile
    APP_DBG_SIG("Ship fire missile\n");
    task_post_pure_msg(PLAYER_MISSILE_TASK_ID, MISSILE_FIRE_SIG);
}

/**
 * @brief Move the ship up by SHIP_Y_STEP.
 *
 * @param None
 * @return None
 */
void player_ship_move_up()
{
    // Bug, ship stuck at y <= 0
    APP_DBG_SIG("Ship move up\n");
    if (myShip.ship.y > 0)
    {
        myShip.ship.y -= SHIP_Y_STEP;
        APP_DBG_SIG("Ship y %d\n", myShip.ship.y);
    }
}

/**
 * @brief Move the ship down by SHIP_Y_STEP.
 *
 * @param None
 * @return None
 */
void player_ship_move_down()
{
    APP_DBG_SIG("Ship move down\n");
    if (myShip.ship.y < LCD_HEIGHT - SHIP_Y_STEP)
    {
        myShip.ship.y += SHIP_Y_STEP;
        APP_DBG_SIG("Ship y %d\n", myShip.ship.y);
    }
    // myShip.ship.y += SHIP_Y_STEP;
    // if (myShip.ship.y > 40)
    // {
    //     myShip.ship.y = 40;
    // }
}

/**
 * @brief Reset the ship.
 *
 * @param None
 * @return None
 */
void player_ship_reset()
{
    APP_DBG_SIG("Ship reset\n");
    myShip.ship.x = SHIP_X_COORDINATE;
    myShip.ship.y = SHIP_Y_COORDINATE;
    myShip.ship.visible = BLACK;
    myShip.ship.action_image = 1;
    myShip.score = 0;
    myShip.fly_speed = 0;
}

/**
 * @brief Handle the ship task.
 *
 * @param None
 * @return None
 */
void player_ship_handler(ak_msg_t* msg)
{
    switch (msg->sig)
    {
    case SHIP_INIT_SIG:
        player_ship_init();
        break;
    case SHIP_FLIGHT_SIG:
        player_ship_flight();
        break;
    case SHIP_FIRE_SIG:
        player_ship_fire();
        break;
    case SHIP_MOVE_UP_SIG:
        player_ship_move_up();
        break;
    case SHIP_MOVE_DOWN_SIG:
        player_ship_move_down();
        break;
    case MISSILE_DESTROY_SIG:
        // TODO: Handle point values data sent by asteroid and enemy ship
        myShip.score += 10;
        APP_DBG_SIG("Ship score %d\n", myShip.score);
        break;
    case SHIP_RESET_SIG:
        player_ship_reset();
        break;
    default:
        break;
    }
}
