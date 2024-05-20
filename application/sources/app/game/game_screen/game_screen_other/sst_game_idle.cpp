#include "sst_game_idle.h"
#include <vector>

#define MAX_CELESTIAL_OBJECTS (60)
class Celestial
{
public:
    int x;
    int y;

    Celestial()
    {
        x = rand() % (LCD_WIDTH - 10);
        y = rand() % (LCD_HEIGHT - 10);
    }

    void celestialDrift()
    {
        x = x - 2;
    }
};
std::vector<Celestial> v_spaces;

void celestial_ilde_render()
{
    for (Celestial p : v_spaces)
    {
        view_render.drawPixel(p.x, p.y, WHITE);
    }
}

void player_ship_idle_draw()
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

void player_ship_idle_flight()
{
    // Cycle through the ship animation
    myShip.ship.action_image++;
    if (myShip.ship.action_image == 4)
    {
        myShip.ship.action_image = 1;
    }
}

static void idle_render();

view_dynamic_t dyn_view_sst_game_idle = {
    {
        .item_type = ITEM_TYPE_DYNAMIC,
    },
    idle_render};

view_screen_t sst_game_idle = {
    &dyn_view_sst_game_idle,
    ITEM_NULL,
    ITEM_NULL,

    .focus_item = 0,
};

void idle_render()
{
    celestial_ilde_render();
    player_ship_idle_draw();
}

void game_idle_handler(ak_msg_t *msg)
{
    switch (msg->sig)
    {
    case SCREEN_ENTRY:
        APP_DBG_SIG("SCREEN_IDLE_ENTRY\n");
        for (int i = 0; i < MAX_CELESTIAL_OBJECTS; i++)
        {
            v_spaces.push_back(Celestial());
        }
        myShip.ship.visible = WHITE;
        myShip.ship.action_image = 1;
        myShip.ship.x = 50;
        myShip.ship.y = 20;
        timer_set(AC_TASK_DISPLAY_ID, AC_DISPLAY_SHOW_IDLE_BALL_MOVING_UPDATE, AC_DISPLAY_SHOW_IDLE_BALL_MOVING_UPDATE_INTERAL, TIMER_PERIODIC);
        break;

    case AC_DISPLAY_SHOW_IDLE_BALL_MOVING_UPDATE:
        for (uint8_t i = 0; i < v_spaces.size(); i++)
        {
            v_spaces[i].celestialDrift();
            if (v_spaces[i].x < 0)
            {
                v_spaces[i].x = (rand() % 10) + 130;
                v_spaces[i].y = rand() % (LCD_HEIGHT - 10);
            }
        }

        player_ship_idle_flight();
        break;

    case AC_DISPLAY_BUTTON_MODE_RELEASED:
        APP_DBG_SIG("AC_DISPLAY_BUTTON_MODE_RELEASED\n");
        timer_remove_attr(AC_TASK_DISPLAY_ID, AC_DISPLAY_SHOW_IDLE_BALL_MOVING_UPDATE);
        task_post_pure_msg(SST_PLAYER_SHIP_TASK_ID, SST_SHIP_RESET_SIG);
        v_spaces.clear();
        SCREEN_TRAN(game_menu_handler, &sst_game_menu);
        break;
    default:
        break;
    }
}