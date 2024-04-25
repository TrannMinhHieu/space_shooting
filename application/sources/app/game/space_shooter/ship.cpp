#include "ship.h"
#include "asteroid.h"

Ship myShip;

void ship_init()
{
    APP_DBG_SIG("Ship init\n");
    myShip.x = AXIS_SHIP_X;
    myShip.y = AXIS_SHIP_Y;
    myShip.visible = WHITE;
    myShip.action_image = 1;
    myShip.score = 0;
}

void ship_flight()
{
    myShip.action_image++;
    if (myShip.action_image == 4)
    {
        myShip.action_image = 1;
    }
}

void ship_fire()
{
    APP_DBG_SIG("Ship fire missile\n");
    task_post_pure_msg(MISSILE_TASK_ID, MISSILE_FIRE_SIG);
}

void ship_move_up()
{
    APP_DBG_SIG("Ship move up\n");
    if (myShip.y > 0)
    {
        myShip.y -= STEP_SHIP_AXIS_Y;
    }
}

void ship_move_down()
{
    APP_DBG_SIG("Ship move down\n");
    if (myShip.y < LCD_HEIGHT - STEP_SHIP_AXIS_Y)
    {
        myShip.y += STEP_SHIP_AXIS_Y;
    }
}

void ship_reset()
{
    APP_DBG_SIG("Ship reset\n");
    myShip.x = AXIS_SHIP_X;
    myShip.y = AXIS_SHIP_Y;
    myShip.visible = BLACK;
    myShip.action_image = 1;
    myShip.score = 0;
    ;
}

void ship_handler(ak_msg_t *msg)
{
    switch (msg->sig)
    {
    case SHIP_INIT_SIG:
        ship_init();
        break;
    case SHIP_FLIGHT_SIG:
        ship_flight();
        break;
    case SHIP_FIRE_SIG:
        ship_fire();
        break;
    case SHIP_MOVE_UP_SIG:
        ship_move_up();
        break;
    case SHIP_MOVE_DOWN_SIG:
        ship_move_down();
        break;
    case MISSILE_DESTROY_SIG:
        myShip.score += 10;
        APP_DBG_SIG("Ship score %d\n", myShip.score);
        break;
    case SHIP_RESET_SIG:
        ship_reset();
        break;
    default:
        break;
    }
}
