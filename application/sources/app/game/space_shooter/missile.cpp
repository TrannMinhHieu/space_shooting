#include "missile.h"
#include "ship.h"
#include "asteroid.h"

Missile myMissile;

void missile_inint()
{
    APP_DBG_SIG("Missile init\n");
    myMissile.x = 0;
    myMissile.y = 0;
    myMissile.visible = BLACK;
    myMissile.action_image = 1;
}

bool is_armed()
{
    if (myMissile.visible == BLACK)
    {
        return true;
    }
    return false;
}
void missile_fired()
{
    if (!is_armed())
    {
        return;
    }
    APP_DBG_SIG("Missile fired\n");
    myMissile.y = myShip.y + 5;
    myMissile.visible = WHITE;
}

void missile_flight()
{
    if (myMissile.visible == WHITE)
    {
        APP_DBG_SIG("Missile in flight\n");
        if (myMissile.x < MAX_MISSILE_DISTANCE)
        {
            myMissile.x += MISSILE_SPEED;
        }
        else if (myMissile.x >= MAX_MISSILE_DISTANCE)
        {
            APP_DBG_SIG("Missile is armed\n");
            myMissile.visible = BLACK;
            myMissile.x = 0;
        }
    }
}

void missile_reset()
{
    APP_DBG_SIG("Missile reset\n");
    myMissile.visible = BLACK;
    myMissile.x = 0;
    myMissile.y = 0;
}

void missile_handler(ak_msg_t *msg)
{
    switch (msg->sig)
    {
    case MISSILE_INIT_SIG:
        missile_inint();
        break;
    case MISSILE_FIRE_SIG:
        missile_fired();
        break;
    case MISSILE_FLIGHT:
        missile_flight();
        break;
    case MISSILE_RESET_SIG:
        missile_reset();
        break;
    default:
        break;
    }
}