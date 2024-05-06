#include "sst_missile.h"

Missile myEnemyMissile[MAX_NUM_OF_ENEMY_MISSILE];

void enemy_missile_inint()
{
    for (uint8_t i = 0; i < MAX_NUM_OF_ENEMY_MISSILE; i++)
    {
        myEnemyMissile[i].visible = BLACK;
        myEnemyMissile[i].x = 0;
        myEnemyMissile[i].y = 0;
        myEnemyMissile[i].action_image = 1;
    }
}

bool is_enemy_missile_out_of_screen(uint8_t enemy_missile_index)
{
    if ((int8_t)(myEnemyMissile[enemy_missile_index].x + SIZE_MISSILE_BITMAP_X) < 0)
    {
        return true;
    }

    return false;
}

bool enemy_missile_missile_collision(uint8_t enemy_missile_index)
{
    if (myMissile.visible == WHITE && myEnemyMissile[enemy_missile_index].visible == WHITE
        && myMissile.x + SIZE_MISSILE_BITMAP_X > myEnemyMissile[enemy_missile_index].x 
        && myMissile.y == myEnemyMissile[enemy_missile_index].y)
    {
        return true;
    }

    return false;
}

bool enemy_missile_ship_collision(uint8_t enemy_missile_index) {
    if (myShip.ship.visible == WHITE && myEnemyMissile[enemy_missile_index].visible == WHITE
        && myShip.ship.x + SIZE_BITMAP_SHIP_X > myEnemyMissile[enemy_missile_index].x 
        && myShip.ship.y == myEnemyMissile[enemy_missile_index].y - SHIP_Y_OFFSET_FOR_MISSILES) 
    {
        return true;
    }

    return false;
}

void enemy_missile_hit()
{
    for (uint8_t i = 0; i < MAX_NUM_OF_ENEMY_MISSILE; i++)
    {
        if (enemy_missile_missile_collision(i))
        {
            APP_DBG_SIG("Enemy missile hit missile\n");
            myExplosion.visible = WHITE;
            myExplosion.x = myEnemyMissile[i].x;
            myExplosion.y = myEnemyMissile[i].y;

            myEnemyMissile[i].visible = BLACK;
            myMissile.visible = BLACK;
            myMissile.x = 0;
            myEnemyMissile[i].x = myEnemyShip.ship.x;
            myEnemyShip.num_missiles++;
        }

        if (enemy_missile_ship_collision(i))
        {
            // TODO: fix bug collision not detected
            APP_DBG_SIG("Enemy missile hit ship\n");
            APP_DBG_SIG("Ship hited by enemy missile no %d\n", i);
            APP_DBG_SIG("Enemy missile no %d position x = %d y = %d\n", i, myEnemyMissile[i].x, myEnemyMissile[i].y);
            myExplosion.visible = WHITE;
            myExplosion.x = myShip.ship.x;
            myExplosion.y = myShip.ship.y;

            myEnemyMissile[i].visible = BLACK;
            myShip.ship.visible = BLACK;
            task_post_pure_msg(GAMEPLAY_TASK_ID, GAME_EXIT);
        }
    }
}

// TODO: missile have to travel "x" pixels before it can be fire again
void enemy_missile_fired()
{
    for (uint8_t i = 0; i < MAX_NUM_OF_ENEMY_MISSILE; i++)
    {
        if (myEnemyMissile[i].visible == BLACK)
        {
            APP_DBG_SIG("Enemy missile fired\n");
            myEnemyMissile[i].x = myEnemyShip.ship.x;
            myEnemyMissile[i].y = myEnemyShip.ship.y + SHIP_Y_OFFSET_FOR_MISSILES;
            myEnemyMissile[i].visible = WHITE;
            break;
            // myEnemyShip.num_missiles--;
        }
    }
}

void enemy_missile_flight()
{
    for (uint8_t i = 0; i < MAX_NUM_OF_ENEMY_MISSILE; i++)
    {
        if (myEnemyMissile[i].visible == WHITE)
        {
            myEnemyMissile[i].x -= myShip.fly_speed;

            if (is_enemy_missile_out_of_screen(i))
            {
                APP_DBG_SIG("Enemy missile out of screen\n");
                myEnemyMissile[i].visible = BLACK;
                myEnemyMissile[i].x = myEnemyShip.ship.x;
                myEnemyMissile[i].y = myEnemyShip.ship.y + SHIP_Y_OFFSET_FOR_MISSILES;
                myEnemyShip.num_missiles++;
            }
        }
    }
}

void enemy_missile_reset()
{
    for (uint8_t i = 0; i < MAX_NUM_OF_ENEMY_MISSILE; i++)
    {
        myEnemyMissile[i].visible = BLACK;
        myEnemyMissile[i].x = 0;
        myEnemyMissile[i].y = 0;
        myEnemyMissile[i].action_image = 1;
    }
}

void enemy_missile_handler(ak_msg_t* msg) {
    switch (msg->sig) {
    case ENEMY_MISSILE_INIT_SIG:
        enemy_missile_inint();
        break;
    case ENEMY_MISSILE_FIRE_SIG:
        enemy_missile_fired();
        break;
    case ENEMY_MISSILE_FLIGHT_SIG:
        enemy_missile_flight();
        break;
    case ENEMY_MISSILE_HIT_SIG:
        enemy_missile_hit();
        break;
    case ENEMY_MISSILE_RESET_SIG:
        enemy_missile_reset();
        break;
    default:
        break;
    }
}