#include "asteroid.h"

Asteroid myAsteroid[NUM_ASTEROIDS];

void asteroid_init()
{
    APP_DBG_SIG("Asteroid init\n");
    const int asteroidYCoordinates[NUM_ASTEROIDS] = {AXIS_Y_ASTEROID_0,
                                                     AXIS_Y_ASTEROID_1,
                                                     AXIS_Y_ASTEROID_2,
                                                     AXIS_Y_ASTEROID_3,
                                                     AXIS_Y_ASTEROID_4,
                                                     AXIS_Y_ASTEROID_5};

    for (uint8_t i = 0; i < NUM_ASTEROIDS; i++)
    {
        myAsteroid[i].y = asteroidYCoordinates[i];
        myAsteroid[i].x = (rand() % 39) + 130;
        myAsteroid[i].visible = WHITE;
        myAsteroid[i].action_image = 1;
    }
}

bool asteroid_out_of_screen()
{
    for (uint8_t i = 0; i < NUM_ASTEROIDS; i++)
    {
        if (myAsteroid[i].x < 0)
        {
            return true;
        }
    }
    return false;
}

void asteroid_flight()
{
    for (uint8_t i = 0; i < NUM_ASTEROIDS; i++)
    {
        if (myAsteroid[i].visible == WHITE)
        {
            myAsteroid[i].x -= ASTEROIDS_SPEED;
            myAsteroid[i].action_image++;
            if (myAsteroid[i].action_image == 4)
            {
                myAsteroid[i].action_image = 1;
            }
            if ((myAsteroid[i].x + SIZE_BITMAP_ASTEROIDS_X) < 0)
            {
                APP_DBG_SIG("Asteroid out of range\n");
                myAsteroid[i].x = (rand() % 39) + 130;
            }
        }
    }
}

void asteroid_hit()
{
    for (uint8_t i = 0; i < NUM_ASTEROIDS; i++)
    {
        // Check if asteroid is visible and hit by missile
        if (myMissile.visible == WHITE && myMissile.x + SIZE_MISSILE_BITMAP_X > myAsteroid[i].x && myMissile.y - 2 == myAsteroid[i].y)
        {
            APP_DBG_SIG("Missile hit asteroid\n");
            APP_DBG_SIG("Asteroid no %d hit by missile\n", i);
            // myAsteroid[i].visible = BLACK;
            myExplosion.visible = WHITE;
            myExplosion.x = myAsteroid[i].x;
            myExplosion.y = myAsteroid[i].y;
            myAsteroid[i].x = (rand() % 39) + 130;

            myMissile.visible = BLACK;
            myMissile.x = 0;
            task_post_pure_msg(SHIP_TASK_ID, MISSILE_DESTROY_SIG);
        }

        // Check if asteroid is visible and hit by ship
        if (myShip.visible == WHITE && myShip.x + SIZE_BITMAP_SHIP_X > myAsteroid[i].x && myShip.y == myAsteroid[i].y - 3)
        {
            APP_DBG_SIG("Ship hit asteroid\n");
            APP_DBG_SIG("Asteroid no %d hit by ship\n", i);
            myExplosion.visible = WHITE;
            myShip.visible = BLACK;
            myExplosion.x = myShip.x;
            myExplosion.y = myShip.y;

            if (myShip.visible == BLACK)
            {
                task_post_pure_msg(GAMEPLAY_TASK_ID, GAME_EXIT);
            }
            else
            {
                task_post_pure_msg(SHIP_TASK_ID, SHIP_HIT_SIG);
                task_post_pure_msg(EXPLOSION_TASK_ID, EXPLPOSION_EXPLODE_SIG);
            }
        }
    }
}

void asteroid_reset() 
{
    APP_DBG_SIG("Asteroid reset\n");
    for (uint8_t i = 0; i < NUM_ASTEROIDS; i++)
    {
        myAsteroid[i].visible = BLACK;
        myAsteroid[i].x = (rand() % 39) + 130;
        myAsteroid[i].action_image = rand() % 3 + 1;
    }
}
void asteroid_handler(ak_msg_t *msg)
{
    switch (msg->sig)
    {
    case ASTEROID_INIT_SIG:
        asteroid_init();
        break;
    case ASTEROID_FLIGHT_SIG:
        asteroid_flight();
        break;
    case SHIP_HIT_SIG:
    case MISSILE_HIT_SIG:
        asteroid_hit();
        break;
    case ASTEROID_RESET_SIG:
        asteroid_reset();
        break;
    default:
        break;
    }
}