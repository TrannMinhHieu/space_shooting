#include "game_screen.h"

uint8_t game_state;

void info_screen_draw()
{
}

/**
 * @brief Draw ship on the screen
 *
 */
void ship_draw()
{
    // If ship is not visible, do nothing and return
    if (myShip.visible != WHITE)
    {
        return;
    }
    switch (myShip.action_image)
    {
    case 1:
        view_render.drawBitmap(myShip.x, myShip.y, bitmap_space_ship_1,
                               SIZE_BITMAP_SHIP_X, SIZE_BITMAP_SHIP_Y, WHITE);
        break;
    case 2:
        view_render.drawBitmap(myShip.x, myShip.y, bitmap_space_ship_2,
                               SIZE_BITMAP_SHIP_X, SIZE_BITMAP_SHIP_Y, WHITE);
        break;
    case 3:
        view_render.drawBitmap(myShip.x, myShip.y, bitmap_space_ship_3,
                               SIZE_BITMAP_SHIP_X, SIZE_BITMAP_SHIP_Y, WHITE);
        break;
    }
}

/**
 * @brief Draw the missile on the screen if it is visible.
 *
 */
void missile_draw()
{
    if (myMissile.visible != WHITE)
    {
        return;
    }
    view_render.drawBitmap(myMissile.x,
                           myMissile.y,
                           bitmap_missile,
                           SIZE_MISSILE_BITMAP_X,
                           SIZE_MISSILE_BITMAP_Y,
                           WHITE);
}

/**
 * @brief Draw asteroids on the screen
 *
 */
void asteroid_draw()
{
    for (uint8_t i = 0; i < NUM_ASTEROIDS; i++)
    {
        // If asteroid is not visible, do nothing and return
        if (myAsteroid[i].visible != WHITE)
        {
            return;
        }
        switch (myAsteroid[i].action_image)
        {
        case 1:
            view_render.drawBitmap(myAsteroid[i].x, myAsteroid[i].y, bitmap_asteroid_1,
                                   SIZE_BITMAP_ASTEROIDS_X, SIZE_BITMAP_ASTEROIDS_Y, WHITE);
            break;
        case 2:
            view_render.drawBitmap(myAsteroid[i].x, myAsteroid[i].y, bitmap_asteroid_2,
                                   SIZE_BITMAP_ASTEROIDS_X, SIZE_BITMAP_ASTEROIDS_Y, WHITE);
            break;
        case 3:
            view_render.drawBitmap(myAsteroid[i].x, myAsteroid[i].y, bitmap_asteroid_3,
                                   SIZE_BITMAP_ASTEROIDS_X, SIZE_BITMAP_ASTEROIDS_Y, WHITE);
            break;
        }
    }
}

/**
 * @brief Draw explosion on the screen
 * 
 */
void explosion_draw()
{
    if (myExplosion.visible != WHITE)
    {
        return;
    }
    if (myExplosion.action_image == 1)
    {
        view_render.drawBitmap(myExplosion.x,
                               myExplosion.y,
                               bitmap_explosion_1,
                               SIZE_BITMAP_EXPLOSION_1_X,
                               SIZE_BITMAP_EXPLOSION_1_Y,
                               WHITE);
    }
    if (myExplosion.action_image == 2)
    {
        view_render.drawBitmap(myExplosion.x,
                               myExplosion.y,
                               bitmap_explosion_2,
                               SIZE_BITMAP_EXPLOSION_2_X,
                               SIZE_BITMAP_EXPLOSION_2_Y,
                               WHITE);
    }
    if (myExplosion.action_image == 3)
    {
        view_render.drawBitmap(myExplosion.x,
                               myExplosion.y,
                               bitmap_explosion_3,
                               SIZE_BITMAP_EXPLOSION_2_X,
                               SIZE_BITMAP_EXPLOSION_2_Y,
                               WHITE);
    }
}

static void space_shooting_gameplay();

view_dynamic_t dyn_view_game = {
    {
        .item_type = ITEM_TYPE_DYNAMIC,
    },
    space_shooting_gameplay};

view_screen_t game_screen = {
    &dyn_view_game,
    ITEM_NULL,
    ITEM_NULL,

    .focus_item = 0,
};

void space_shooting_gameplay()
{
    if (game_state == GAME_PLAY)
    {
        ship_draw();
        asteroid_draw();
        missile_draw();
        explosion_draw();
        view_render.update();
    }
    else if (game_state == GAME_OVER)
    {
        view_render.clear();
        view_render.setTextSize(2);
        view_render.setTextColor(WHITE);
        view_render.setCursor(17, 24);
        view_render.print("YOU LOSE");
    }
}
/*****************************************************************************/
/* GAME HANDLER */
/*****************************************************************************/
void game_time_tick_setup()
{
    timer_set(AC_TASK_DISPLAY_ID, GAMEPLAY_TIME_TICK, GAMEPLAY_TIME_TICK_INTERVAL, TIMER_PERIODIC);
}

void game_play_handler(ak_msg_t *msg)
{
    switch (msg->sig)
    {
    case SCREEN_ENTRY:
        APP_DBG_SIG("SCREEN_GAME_PLAY_ENTRY\n");
        task_post_pure_msg(SHIP_TASK_ID, SHIP_INIT_SIG);
        task_post_pure_msg(MISSILE_TASK_ID, MISSILE_INIT_SIG);
        task_post_pure_msg(ASTEROID_TASK_ID, ASTEROID_INIT_SIG);
        task_post_pure_msg(EXPLOSION_TASK_ID, EXPLOSION_INIT_SIG);
        game_time_tick_setup();
        game_state = GAME_PLAY;
        break;
    case GAMEPLAY_TIME_TICK:
        task_post_pure_msg(SHIP_TASK_ID, SHIP_FLIGHT_SIG);
        task_post_pure_msg(MISSILE_TASK_ID, MISSILE_FLIGHT);
        task_post_pure_msg(ASTEROID_TASK_ID, ASTEROID_FLIGHT_SIG);
        task_post_pure_msg(ASTEROID_TASK_ID, ASTEROID_HIT_SIG);
        task_post_pure_msg(EXPLOSION_TASK_ID, EXPLPOSION_EXPLODE_SIG);
        break;
    case GAME_EXIT:
        task_post_pure_msg(SHIP_TASK_ID, SHIP_RESET_SIG);
        task_post_pure_msg(MISSILE_TASK_ID, MISSILE_RESET_SIG);
        task_post_pure_msg(ASTEROID_TASK_ID, ASTEROID_RESET_SIG);
        task_post_pure_msg(EXPLOSION_TASK_ID, EXPLOSION_RESET_SIG);

        timer_set(AC_TASK_DISPLAY_ID, AC_DISPLAY_SHOW_GAME_MENU, GAMEPLAY_TIME_EXIT_INTERVAL, TIMER_ONE_SHOT);
        game_state = GAME_OVER;
        break;

    case AC_DISPLAY_SHOW_GAME_MENU:
        SCREEN_TRAN(game_menu_handler, &game_menu);
        break;

    default:
        break;
    }
}