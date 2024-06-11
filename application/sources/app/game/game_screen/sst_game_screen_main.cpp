#include "sst_game_screen.h"

uint8_t sst_game_state;
uint8_t sst_game_stage;
uint8_t total_health;

void sst_asteroid_draw();
void sst_player_ship_draw();
void sst_player_missile_draw();
void sst_enemy_ship_draw();
void sst_enemy_missile_draw();
void sst_terrain_draw();
void sst_explosion_draw();

void sst_game_stage_control();

static void sst_space_shooting_gameplay_render();

view_dynamic_t dyn_view_sst_game_screen = {
    {
        .item_type = ITEM_TYPE_DYNAMIC,
    },
    sst_space_shooting_gameplay_render};

view_screen_t sst_game_screen = {
    &dyn_view_sst_game_screen,
    ITEM_NULL,
    ITEM_NULL,

    .focus_item = 0,
};

void sst_space_shooting_gameplay_render()
{
#define TEXT_TITLE_X (17)
#define TEXT_TITLE_Y_1 (24)
#define TEXT_TITLE_Y_2 (TEXT_TITLE_Y_1 + 20)

#define TEXT_SCORE_X (97)
#define TEXT_SCORE_Y (TEXT_TITLE_Y_2)
    static uint8_t x_missile_display = 7;
    if (sst_game_state == GAME_PLAY)
    {
        sst_asteroid_draw();
        sst_explosion_draw();
        if (myExplosion.visible == WHITE)
        {
            view_render.setCursor(myExplosion.x - 20, myExplosion.y);
            if (sst_game_stage == GAME_STAGE_ASTEROID_FEILD)
            {
                view_render.print("+10");
            }
            else if (sst_game_stage == GAME_STAGE_SHIP_FIGHT)
            {
                if (myEnemyShip.ship.visible != WHITE)
                {

                    view_render.print("+100");
                }
            }
        }
        sst_terrain_draw();

        sst_player_ship_draw();
        sst_player_missile_draw();

        sst_enemy_ship_draw();
        sst_enemy_missile_draw();
        if (sst_game_stage == GAME_STAGE_SHIP_FIGHT)
        {
            // Display enemy health bar
            APP_DBG_SIG("total health %d\n", total_health);
            view_render.drawRoundRect(10, 55, 110, 5, 2, WHITE);
            view_render.fillRoundRect(10, 55, myEnemyShip.health * (110 / total_health), 5, 2, WHITE);
        }
        else
        {
            view_render.setTextSize(1);
            view_render.setTextColor(WHITE);
            // view_render.setCursor(2,55);
            view_render.setCursor(65, 55);
            view_render.print("Score:");
            view_render.print(myShip.score);
            view_render.drawLine(0, LCD_HEIGHT + 5, LCD_WIDTH, LCD_HEIGHT + 5, WHITE);
            // view_render.drawLine(0, LCD_HEIGHT-10, 	LCD_WIDTH, LCD_HEIGHT-10,	WHITE);
            
            // make missile cooldown effect
            view_render.drawRoundRect(0, 54, SIZE_BITMAP_MISSILE_Y + 20, SIZE_BITMAP_MISSILE_Y + 2, 2, WHITE);
            APP_DBG_SIG("arm_missile_interval %d\n", arm_missile_interval);
            view_render.fillRoundRect(0, 54, (SIZE_BITMAP_MISSILE_Y + 20) / arm_missile_interval, SIZE_BITMAP_MISSILE_Y + 2, 2, WHITE);
            if(v_myPlayerMissiles.size() < 3){
            view_render.drawBitmap(x_missile_display, 55, sst_bitmap_missile, SIZE_BITMAP_MISSILE_X, SIZE_BITMAP_MISSILE_Y, WHITE);}
            // if (myMissile.visible == WHITE)
            // {
            //     x_missile_display++;
            //     if (x_missile_display == 15)
            //     {
            //         x_missile_display = 2;
            //     }
            // }
            // else
            // {
            //     x_missile_display = 2;
            // }
        }
        view_render.update();
    }
    else if (sst_game_state == GAME_OVER)
    {
        view_render.clear();
        view_render.setTextSize(2);
        view_render.setTextColor(WHITE);
        view_render.setCursor(TEXT_TITLE_X, TEXT_TITLE_Y_1);
        view_render.print("YOU LOSE");

        view_render.setTextSize(1);
        view_render.setCursor(TEXT_TITLE_X, TEXT_TITLE_Y_2);
        view_render.print("YOUR SCORE: ");

        view_render.setCursor(TEXT_SCORE_X, TEXT_SCORE_Y);
        view_render.print(sst_game_score.current_score);
    }
}
/*****************************************************************************/
/* GAME HANDLER */
/*****************************************************************************/
void sst_game_time_tick_setup()
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
        sst_game_stage = GAME_STAGE_ASTEROID_FEILD;
        sst_game_state = GAME_PLAY;
        sst_game_time_tick_setup();
        break;
    case GAMEPLAY_TIME_TICK:
        task_post_pure_msg(SST_PLAYER_SHIP_TASK_ID, SST_SHIP_FLIGHT_SIG);
        task_post_pure_msg(SST_PLAYER_MISSILE_TASK_ID, SST_MISSILE_FLIGHT_SIG);
        task_post_pure_msg(SST_EXPLOSION_TASK_ID, SST_EXPLPOSION_EXPLODE_SIG);
        sst_game_stage_control();
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
        BUZZER_PlayTones(tones_3beep);
        sst_game_state = GAME_OVER;
        break;

    case AC_DISPLAY_SHOW_GAME_HIGHSCORE:
        timer_remove_attr(AC_TASK_DISPLAY_ID, GAMEPLAY_TIME_TICK);
        SCREEN_TRAN(sst_game_highscore_handler, &sst_game_highscore);
        sst_game_score.current_score = 0;
        break;

    default:
        break;
    }
}

// FUNCTION DEFINITION

/**
 * Controls the game stage and posts messages based on the current game stage.
 *
 * @throws None
 */
void sst_game_stage_control()
{
    // Post messages based on the current game stage
    if (sst_game_stage == GAME_STAGE_SHIP_FIGHT)
    {
        task_post_pure_msg(SST_ENEMY_MISSILE_TASK_ID, SST_ENEMY_MISSILE_FLIGHT_SIG);
        task_post_pure_msg(SST_ENEMY_SHIP_TASK_ID, SST_ENEMY_SHIP_FLIGHT_SIG);
    }
    if (sst_game_stage == GAME_STAGE_ASTEROID_FEILD)
    {
        task_post_pure_msg(SST_ASTEROID_TASK_ID, SST_ASTEROID_FLIGHT_SIG);
    }
    if (sst_game_stage == GAME_STAGE_TERRAIN)
    {
        if (myShip.ship.y < 40)
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
void sst_asteroid_draw()
{
    for (uint8_t i = 0; i < NUM_ASTEROIDS; i++)
    {
        // If asteroid is not visible, do nothing and return
        if (myAsteroid[i].visible != WHITE)
        {
            return;
        }
        const uint8_t *asteroidBitmaps[] = {nullptr, sst_bitmap_asteroid_1, sst_bitmap_asteroid_2, sst_bitmap_asteroid_3};

        if (myAsteroid[i].action_image >= 1 && myAsteroid[i].action_image <= 3)
        {
            view_render.drawBitmap(myAsteroid[i].x, myAsteroid[i].y, asteroidBitmaps[myAsteroid[i].action_image],
                                   SIZE_BITMAP_ASTEROIDS_X, SIZE_BITMAP_ASTEROIDS_Y, WHITE);
        }
    }
}

/**
 * @brief Draw explosion on the screen
 *
 */
void sst_explosion_draw()
{
    if (myExplosion.visible != WHITE)
    {
        return;
    }
    const uint8_t *explosionBitmaps[] = {nullptr, sst_bitmap_explosion_1, sst_bitmap_explosion_2, sst_bitmap_explosion_3};

    if (myExplosion.action_image >= 1 && myExplosion.action_image <= 3)
    {
        view_render.drawBitmap(myExplosion.x, myExplosion.y, explosionBitmaps[myExplosion.action_image],
                               SIZE_BITMAP_EXPLOSION_X, SIZE_BITMAP_EXPLOSION_Y, WHITE);
    }
}

/**
 * @brief Draw ship on the screen
 *
 */
void sst_player_ship_draw()
{
    // If ship is not visible, do nothing and return
    if (myShip.ship.visible != WHITE)
    {
        return;
    }
    const uint8_t *playerShipBitmaps[] = {nullptr, sst_bitmap_space_ship_1, sst_bitmap_space_ship_2, sst_bitmap_space_ship_3};

    if (myShip.ship.action_image >= 1 && myShip.ship.action_image <= 3)
    {
        view_render.drawBitmap(myShip.ship.x, myShip.ship.y, playerShipBitmaps[myShip.ship.action_image],
                               SIZE_BITMAP_SHIP_X, SIZE_BITMAP_SHIP_Y, WHITE);
    }
}
/**
 * @brief Draw the missile on the screen if it is visible.
 *
 */
void sst_player_missile_draw()
{
    for (uint8_t i = 0; i < v_myPlayerMissiles.size(); i++)
    {
        if (v_myPlayerMissiles[i].visible != WHITE)
        {
            return;
        }
        view_render.drawBitmap(v_myPlayerMissiles[i].x,
                               v_myPlayerMissiles[i].y,
                               sst_bitmap_missile,
                               SIZE_BITMAP_MISSILE_X,
                               SIZE_BITMAP_MISSILE_Y,
                               WHITE);
    }
}
/**
 * Draws the enemy ship on the screen if it is visible.
 *
 * @return void
 *
 * @throws None
 */
void sst_enemy_ship_draw()
{
    if (myEnemyShip.ship.visible != WHITE)
    {
        return;
    }
    const uint8_t *enemyShipBitmaps[] = {nullptr, sst_bitmap_space_ship_1, sst_bitmap_space_ship_2, sst_bitmap_space_ship_3};

    if (myEnemyShip.ship.action_image >= 1 && myEnemyShip.ship.action_image <= 3)
    {
        view_render.drawBitmap(myEnemyShip.ship.x, myEnemyShip.ship.y, enemyShipBitmaps[myEnemyShip.ship.action_image],
                               SIZE_BITMAP_SHIP_X, SIZE_BITMAP_SHIP_Y, WHITE);
    }
}
/**
 * Draws the enemy missile on the screen if it is visible.
 *
 * @return void
 *
 * @throws None
 */
void sst_enemy_missile_draw()
{
    for (uint8_t i = 0; i < v_myEnemyMissiles.size(); i++)
    {
        if (v_myEnemyMissiles[i].visible != WHITE)
        {
            return;
        }
        view_render.drawBitmap(v_myEnemyMissiles[i].x,
                               v_myEnemyMissiles[i].y,
                               sst_bitmap_missile_enemy,
                               SIZE_BITMAP_MISSILE_X,
                               SIZE_BITMAP_MISSILE_Y,
                               WHITE);
    }
}

void sst_terrain_draw()
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