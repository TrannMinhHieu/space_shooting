#include "sst_game_screen.h"

uint8_t sst_game_state;
uint8_t sst_game_stage;

/**
 * Controls the game stage and posts messages based on the current game stage.
 *
 * @throws None
 */
void game_stage_control()
{
    // Post messages based on the current game stage
    if (sst_game_stage == GAME_STAGE_SHIP_FIGHT)
    {
        task_post_pure_msg(SST_PLAYER_MISSILE_TASK_ID, SST_MISSILE_HIT_SIG);
        task_post_pure_msg(SST_ENEMY_MISSILE_TASK_ID, SST_ENEMY_MISSILE_FLIGHT_SIG);
        task_post_pure_msg(SST_ENEMY_MISSILE_TASK_ID, SST_ENEMY_MISSILE_HIT_SIG);
        task_post_pure_msg(SST_ENEMY_SHIP_TASK_ID, SST_ENEMY_SHIP_FLIGHT_SIG);
    }
    if (sst_game_stage == GAME_STAGE_ASTEROID_FEILD)
    {
        task_post_pure_msg(SST_ASTEROID_TASK_ID, SST_ASTEROID_FLIGHT_SIG);
        task_post_pure_msg(SST_ASTEROID_TASK_ID, SST_ASTEROID_HIT_SIG);
    }
    if (sst_game_stage == GAME_STAGE_TERRAIN)
    {
        if (myShip.ship.y < LCD_HEIGHT - SHIP_Y_STEP)
        {
            myShip.ship.y++;
        }
        task_post_pure_msg(SST_TERRAIN_TASK_ID, SST_TERRAIN_UPDATE_SIG);
    }
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
            view_render.drawBitmap(myAsteroid[i].x, myAsteroid[i].y, sst_bitmap_asteroid_1,
                                   SIZE_BITMAP_ASTEROIDS_X, SIZE_BITMAP_ASTEROIDS_Y, WHITE);
            break;
        case 2:
            view_render.drawBitmap(myAsteroid[i].x, myAsteroid[i].y, sst_bitmap_asteroid_2,
                                   SIZE_BITMAP_ASTEROIDS_X, SIZE_BITMAP_ASTEROIDS_Y, WHITE);
            break;
        case 3:
            view_render.drawBitmap(myAsteroid[i].x, myAsteroid[i].y, sst_bitmap_asteroid_3,
                                   SIZE_BITMAP_ASTEROIDS_X, SIZE_BITMAP_ASTEROIDS_Y, WHITE);
            break;
        default:
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
    switch (myExplosion.action_image)
    {
    case 1:
        view_render.drawBitmap(myExplosion.x, myExplosion.y, sst_bitmap_explosion_1,
                               SIZE_BITMAP_EXPLOSION_1_X, SIZE_BITMAP_EXPLOSION_1_Y, WHITE);
        break;
    case 2:
        view_render.drawBitmap(myExplosion.x, myExplosion.y, sst_bitmap_explosion_2,
                               SIZE_BITMAP_EXPLOSION_2_X, SIZE_BITMAP_EXPLOSION_2_Y, WHITE);
        break;
    case 3:
        view_render.drawBitmap(myExplosion.x, myExplosion.y, sst_bitmap_explosion_3,
                               SIZE_BITMAP_EXPLOSION_2_X, SIZE_BITMAP_EXPLOSION_2_Y, WHITE);
        break;
    default:
        break;
    }
}

/**
 * @brief Draw ship on the screen
 *
 */
void player_ship_draw()
{
    // If ship is not visible, do nothing and return
    if (myShip.ship.visible != WHITE)
    {
        return;
    }
    switch (myShip.ship.action_image)
    {
    case 1:
        view_render.drawBitmap(myShip.ship.x, myShip.ship.y, sst_bitmap_space_ship_1,
                               SIZE_BITMAP_SHIP_X, SIZE_BITMAP_SHIP_Y, WHITE);
        break;
    case 2:
        view_render.drawBitmap(myShip.ship.x, myShip.ship.y, sst_bitmap_space_ship_2,
                               SIZE_BITMAP_SHIP_X, SIZE_BITMAP_SHIP_Y, WHITE);
        break;
    case 3:
        view_render.drawBitmap(myShip.ship.x, myShip.ship.y, sst_bitmap_space_ship_3,
                               SIZE_BITMAP_SHIP_X, SIZE_BITMAP_SHIP_Y, WHITE);
        break;
    default:
        break;
    }
}
/**
 * @brief Draw the missile on the screen if it is visible.
 *
 */
void player_missile_draw()
{
    if (myMissile.visible != WHITE)
    {
        return;
    }
    view_render.drawBitmap(myMissile.x,
                           myMissile.y,
                           sst_bitmap_missile,
                           SIZE_MISSILE_BITMAP_X,
                           SIZE_MISSILE_BITMAP_Y,
                           WHITE);
}

/**
 * Draws the enemy ship on the screen if it is visible.
 *
 * @return void
 *
 * @throws None
 */
void enemy_ship_draw()
{
    if (myEnemyShip.ship.visible != WHITE)
    {
        return;
    }

    switch (myEnemyShip.ship.action_image)
    {
    case 1:
        view_render.drawBitmap(myEnemyShip.ship.x, myEnemyShip.ship.y, sst_bitmap_space_ship_1,
                               SIZE_BITMAP_SHIP_X, SIZE_BITMAP_SHIP_Y, WHITE);
        break;
    case 2:
        view_render.drawBitmap(myEnemyShip.ship.x, myEnemyShip.ship.y, sst_bitmap_space_ship_2,
                               SIZE_BITMAP_SHIP_X, SIZE_BITMAP_SHIP_Y, WHITE);
        break;
    case 3:
        view_render.drawBitmap(myEnemyShip.ship.x, myEnemyShip.ship.y, sst_bitmap_space_ship_3,
                               SIZE_BITMAP_SHIP_X, SIZE_BITMAP_SHIP_Y, WHITE);
        break;
    default:
        break;
    }
}
/**
 * Draws the enemy missile on the screen if it is visible.
 *
 * @return void
 *
 * @throws None
 */
void enemy_missile_draw()
{
    for (uint8_t i = 0; i < v_myEnemyMissiles.size(); i++)
    {
        if (v_myEnemyMissiles[i].visible != WHITE)
        {
            continue;
        }
        view_render.drawBitmap(v_myEnemyMissiles[i].x,
                               v_myEnemyMissiles[i].y,
                               sst_bitmap_missile_enemy,
                               SIZE_MISSILE_BITMAP_X,
                               SIZE_MISSILE_BITMAP_Y,
                               WHITE);
    }
}

void terrain_draw()
{
    if (v_terrain.size() < 1)
    {
        return;
    }

    for (uint8_t i = 1; i < v_terrain.size(); i++)
    {
        view_render.drawLine(v_terrain[i - 1].x, v_terrain[i - 1].y, v_terrain[i].x, v_terrain[i].y, WHITE);
    }
}

static void space_shooting_gameplay_render();

view_dynamic_t dyn_view_sst_game_screen = {
    {
        .item_type = ITEM_TYPE_DYNAMIC,
    },
    space_shooting_gameplay_render};

view_screen_t sst_game_screen = {
    &dyn_view_sst_game_screen,
    ITEM_NULL,
    ITEM_NULL,

    .focus_item = 0,
};

void space_shooting_gameplay_render()
{
    if (sst_game_state == GAME_PLAY)
    {
        asteroid_draw();
        explosion_draw();
        terrain_draw();

        player_ship_draw();
        player_missile_draw();

        enemy_ship_draw();
        enemy_missile_draw();
        view_render.update();
    }
    else if (sst_game_state == GAME_OVER)
    {
        view_render.clear();
        view_render.setTextSize(2);
        view_render.setTextColor(WHITE);
        view_render.setCursor(17, 24);
        view_render.print("YOU LOSE");

        view_render.setTextSize(1);
        view_render.setCursor(17, 44);
        view_render.print("YOUR SCORE: ");

        view_render.setCursor(97, 44);
        view_render.print(sst_game_score.current_score);
    }
}
/*****************************************************************************/
/* GAME HANDLER */
/*****************************************************************************/
void game_time_tick_setup()
{
    timer_set(AC_TASK_DISPLAY_ID, GAMEPLAY_TIME_TICK, GAMEPLAY_TIME_TICK_INTERVAL, TIMER_PERIODIC);
}

void sst_game_play_handler(ak_msg_t *msg)
{
    switch (msg->sig)
    {
    case SCREEN_ENTRY:
        APP_DBG_SIG("SCREEN_GAME_PLAY_ENTRY\n");
        task_post_pure_msg(SST_ASTEROID_TASK_ID, SST_ASTEROID_INIT_SIG);
        task_post_pure_msg(SST_EXPLOSION_TASK_ID, SST_EXPLOSION_INIT_SIG);
        task_post_pure_msg(SST_TERRAIN_TASK_ID, SST_TERRAIN_INIT_SIG);

        task_post_pure_msg(SST_PLAYER_SHIP_TASK_ID, SST_SHIP_INIT_SIG);
        task_post_pure_msg(SST_PLAYER_MISSILE_TASK_ID, SST_MISSILE_INIT_SIG);

        task_post_pure_msg(SST_ENEMY_SHIP_TASK_ID, SST_ENEMY_SHIP_INIT_SIG);
        task_post_pure_msg(SST_ENEMY_MISSILE_TASK_ID, SST_ENEMY_MISSILE_INIT_SIG);
        sst_game_stage = GAME_STAGE_TERRAIN;
        sst_game_state = GAME_PLAY;
        game_time_tick_setup();
        break;
    case GAMEPLAY_TIME_TICK:
        task_post_pure_msg(SST_PLAYER_SHIP_TASK_ID, SST_SHIP_FLIGHT_SIG);
        task_post_pure_msg(SST_PLAYER_MISSILE_TASK_ID, SST_MISSILE_FLIGHT_SIG);
        task_post_pure_msg(SST_EXPLOSION_TASK_ID, SST_EXPLPOSION_EXPLODE_SIG);
        game_stage_control();
        break;
    case GAME_EXIT:
        APP_DBG_SIG("SCREEN_GAME_EXIT\n");
        sst_game_score.current_score = myShip.score;
        task_post_pure_msg(SST_ASTEROID_TASK_ID, SST_ASTEROID_RESET_SIG);
        task_post_pure_msg(SST_EXPLOSION_TASK_ID, SST_EXPLOSION_RESET_SIG);
        task_post_pure_msg(SST_TERRAIN_TASK_ID, SST_TERRAIN_RESET_SIG);
        task_post_pure_msg(SST_PLAYER_SHIP_TASK_ID, SST_SHIP_RESET_SIG);
        task_post_pure_msg(SST_PLAYER_MISSILE_TASK_ID, SST_MISSILE_RESET_SIG);
        task_post_pure_msg(SST_ENEMY_SHIP_TASK_ID, SST_ENEMY_SHIP_RESET_SIG);
        task_post_pure_msg(SST_ENEMY_MISSILE_TASK_ID, SST_ENEMY_MISSILE_RESET_SIG);

        timer_set(AC_TASK_DISPLAY_ID, AC_DISPLAY_SHOW_GAME_HIGHSCORE, GAMEPLAY_TIME_EXIT_INTERVAL, TIMER_ONE_SHOT);
        sst_game_state = GAME_OVER;
        break;

    case AC_DISPLAY_SHOW_GAME_HIGHSCORE:
        SCREEN_TRAN(game_highscore_handler, &sst_game_highscore);
        sst_game_score.current_score = 0;
        break;

    default:
        break;
    }
}