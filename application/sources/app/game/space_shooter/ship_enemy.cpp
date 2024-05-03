#include "ship.h"

EnemyShip myEnemyShip;

void enemy_ship_init()
{
    APP_DBG_SIG("Enemy ship init\n");
    myEnemyShip.ship.x = 0;
    myEnemyShip.ship.y = 0;
    myEnemyShip.ship.visible = BLACK;
    myEnemyShip.ship.action_image = 1;
    myEnemyShip.health = 3;
    myEnemyShip.num_missiles = MAX_NUM_OF_ENEMY_MISSILE;
}

uint8_t ship_control;
enum Actions
{
    MOVE_UP,
    MOVE_DOWN,
    FIRE,
    DO_NOTTHING
};
int8_t randomize_enemy_ship_control()
{
    // TODO: use better randomize function
    // std::random_device rd;
    // std::mt19937 gen(rd());
    // std::uniform_int_distribution<int> dis(0, 99);
    // int random = dis(gen);
    uint8_t random = rand() % 100;

    // 30% chance to move up
    // 30% chance to move down
    // 20% chance to fire
    if (random < 5)
    {
        task_post_pure_msg(SHIP_ENEMY_TASK_ID, SHIP_ENEMY_MOVE_SIG);
        return MOVE_UP;
    }
    else if (random < 10)
    {
        task_post_pure_msg(SHIP_ENEMY_TASK_ID, SHIP_ENEMY_MOVE_SIG);
        return MOVE_DOWN;
    }
    else if (random < 17)
    {
        task_post_pure_msg(SHIP_ENEMY_TASK_ID, SHIP_ENEMY_FIRE_SIG);
        return FIRE;
    }

    return DO_NOTTHING;
}

void enemy_ship_takeoff()
{
    APP_DBG_SIG("Enemy ship takeoff\n");
    myEnemyShip.ship.x = 150;
    myEnemyShip.ship.y = 20;
    myEnemyShip.ship.visible = WHITE;
    myEnemyShip.ship.action_image = 1;
}

void enemy_ship_retreat()
{
    APP_DBG_SIG("Enemy ship retreat\n");
    if (myEnemyShip.ship.x + SIZE_BITMAP_SHIP_X < LCD_WIDTH)
    {
        myEnemyShip.ship.x++;
    }
}

void enemy_ship_flight()
{
    if (myEnemyShip.ship.visible != WHITE)
    {
        return;
    }

    if (myEnemyShip.ship.x > 100)
    {
        myEnemyShip.ship.x -= 2;
        myEnemyShip.ship.action_image++;
        if (myEnemyShip.ship.action_image == 4)
        {
            myEnemyShip.ship.action_image = 1;
        }
    }
    else
    {
        myEnemyShip.ship.action_image++;
        if (myEnemyShip.ship.action_image == 4)
        {
            myEnemyShip.ship.action_image = 1;
            ship_control = randomize_enemy_ship_control();
        }
    }
}
void enemy_ship_move()
{
    if (myEnemyShip.ship.visible != WHITE || myEnemyShip.ship.x > 100)
    {
        return;
    }

    if (myEnemyShip.ship.y > 0 && ship_control == MOVE_UP)
    {
        APP_DBG_SIG("Enemy ship move up\n");
        myEnemyShip.ship.y -= SHIP_Y_STEP;
    }

    if (myEnemyShip.ship.y < LCD_HEIGHT - SHIP_Y_STEP && ship_control == MOVE_DOWN)
    {
        APP_DBG_SIG("Enemy ship move down\n");
        myEnemyShip.ship.y += SHIP_Y_STEP;
    }
}

void enemy_ship_fire()
{
    // Send message to fire a missile
    if (ship_control != FIRE || myEnemyShip.num_missiles <= 0)
    {
        return;
    }

    {
        APP_DBG_SIG("Enemy ship fire missile\n");
        myEnemyShip.num_missiles--;
        // task_post_pure_msg(MISSILE_TASK_ID, MISSILE_FIRE_SIG);
    }
    // TODO: send message to fire a missile
    // TODO: fly out if num_missiles =< 0
}

void enemy_ship_reset()
{
    APP_DBG_SIG("Enemy ship reset\n");
    myEnemyShip.ship.x = 0;
    myEnemyShip.ship.y = 0;
    myEnemyShip.ship.visible = BLACK;
    myEnemyShip.ship.action_image = 1;
    myEnemyShip.num_missiles = MAX_NUM_OF_ENEMY_MISSILE;
}

void enemy_ship_handler(ak_msg_t *msg)
{
    switch (msg->sig)
    {
    case SHIP_ENEMY_INIT_SIG:
        enemy_ship_init();
        break;
    case SHIP_ENEMY_TAKEOFF_SIG:
        enemy_ship_takeoff();
        break;
    case SHIP_ENEMY_FLIGHT_SIG:
        enemy_ship_flight();
        break;
    case SHIP_ENEMY_MOVE_SIG:
        enemy_ship_move();
        break;
    case SHIP_ENEMY_FIRE_SIG:
        enemy_ship_fire();
        break;
    case MISSILE_DESTROY_SIG:
        myEnemyShip.num_missiles--;
        break;
    case SHIP_ENEMY_RESET_SIG:
        enemy_ship_reset();
        break;
    default:
        break;
    }
}