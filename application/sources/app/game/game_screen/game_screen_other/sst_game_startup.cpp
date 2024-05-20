#include "sst_game_startup.h"

static void sst_startup_render();

view_dynamic_t dyn_view_sst_game_startup = {
    {
        .item_type = ITEM_TYPE_DYNAMIC,
    },
    sst_startup_render};

view_screen_t sst_game_startup = {
    &dyn_view_sst_game_startup,
    ITEM_NULL,
    ITEM_NULL,

    .focus_item = 0,
};

void sst_startup_render()
{
#define TEXT_TITLE_X        (5)
#define TEXT_TITLE_1_Y      (10)
#define TEXT_TITLE_2_Y      (TEXT_TITLE_1_Y + 17)

#define TEXT_NORMAL_X       (TEXT_TITLE_X)
#define TEXT_NORMAL_Y       (50)

#define SPACE_SHIP_ICON_X   (105)
#define SPACE_SHIP_ICON_Y   (TEXT_TITLE_2_Y)

    view_render.clear();
    view_render.setCursor(TEXT_TITLE_X, TEXT_TITLE_1_Y);
    view_render.setTextSize(2);
    view_render.setTextColor(WHITE);
    view_render.print("SPACE");
    view_render.setCursor(TEXT_TITLE_X, TEXT_TITLE_2_Y);
    view_render.print("SHOOTING");

    view_render.drawBitmap(SPACE_SHIP_ICON_X, SPACE_SHIP_ICON_Y, sst_bitmap_space_ship_1, SIZE_BITMAP_SHIP_X, SIZE_BITMAP_SHIP_Y, WHITE);

    view_render.setCursor(TEXT_TITLE_X, TEXT_NORMAL_Y);
    view_render.setTextSize(1);
    view_render.print("Starting...");
}

void sst_game_startup_handler(ak_msg_t *msg)
{
    switch (msg->sig)
    {
    case AC_DISPLAY_INITIAL:
    {
        APP_DBG_SIG("AC_DISPLAY_INITIAL\n");
        view_render.initialize();
        view_render_display_on();
        timer_set(AC_TASK_DISPLAY_ID, AC_DISPLAY_SHOW_GAME_MENU, AC_DISPLAY_STARTUP_INTERVAL, TIMER_ONE_SHOT);
    }
    break;

    case AC_DISPLAY_BUTTON_MODE_RELEASED:
    {
        APP_DBG_SIG("AC_DISPLAY_BUTON_MODE_RELEASED\n");
        timer_remove_attr(AC_TASK_DISPLAY_ID, AC_DISPLAY_SHOW_GAME_MENU);
        SCREEN_TRAN(sst_game_menu_handler, &sst_game_menu);
    }
    break;

    case AC_DISPLAY_SHOW_GAME_MENU:
    {
        APP_DBG_SIG("AC_DISPLAY_SHOW_GAME_PLAY\n");
        SCREEN_TRAN(sst_game_menu_handler, &sst_game_menu);
    }
    break;

    default:
        break;
    }
}