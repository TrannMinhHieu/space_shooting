#include "explosion.h"

#include "asteroid.h"
#include "missile.h"
#include "ship.h"

Explosion myExplosion;

void explosion_init()
{
    APP_DBG_SIG("Explosion init\n");
    myExplosion.visible = BLACK;
    myExplosion.x = 0;
    myExplosion.y = 0;
    myExplosion.action_image = 1;
}

void explosion_explode()
{
    if (myExplosion.visible != WHITE)
    {
        return;
    }
    APP_DBG_SIG("Explosion explode\n");
    myExplosion.action_image++;
    if (myExplosion.action_image == 4)
    {
        myExplosion.action_image = 1;
        myExplosion.visible = BLACK;
    }
}

void explosion_handler(ak_msg_t *msg)
{
    switch (msg->sig)
    {
    case EXPLOSION_INIT_SIG:
    {
        explosion_init();
    }
    break;
    case EXPLPOSION_EXPLODE_SIG:
    {
        explosion_explode();
    }
    break;
    default:
        break;
    }
}