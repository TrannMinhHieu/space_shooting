#include "missile.h"

EnemyMissile myEnemyMissile[MAX_NUM_OF_ENEMY_MISSILE];

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
    if (myMissile.visible == WHITE && myMissile.x + SIZE_MISSILE_BITMAP_X > myEnemyMissile[enemy_missile_index].x && myMissile.y == myEnemyMissile[enemy_missile_index].y)
    {
        return true;
    }

    return false;
}

bool enemy_missile_ship_collision(uint8_t enemy_missile_index) {}

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
            myEnemyShip.num_missiles++;
        }

        if (enemy_missile_ship_collision(i))
        {
            APP_DBG_SIG("Enemy missile hit ship\n");
            myExplosion.visible = WHITE;
            myExplosion.x = myShip.ship.x;
            myExplosion.y = myShip.ship.y;

            myEnemyMissile[i].visible = BLACK;
            myShip.ship.visible = BLACK;
            task_post_pure_msg(GAMEPLAY_TASK_ID, GAME_EXIT);
        }
    }
}

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
                APP_DBG_SIG("Missile out of screen\n");
                myEnemyMissile[i].visible = BLACK;
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