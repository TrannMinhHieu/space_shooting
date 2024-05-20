#include "sst_game_highscore.h"

sst_game_score_t sst_game_score;

static void sst_highscore_render();

view_dynamic_t dyn_view_sst_game_highscore = {
    {
        .item_type = ITEM_TYPE_DYNAMIC,
    },
    sst_highscore_render};

view_screen_t sst_game_highscore = {
    &dyn_view_sst_game_highscore,
    ITEM_NULL,
    ITEM_NULL,

    .focus_item = 0,
};

void sst_highscore_render()
{
#define TEXT_TITLE_X		(5)
#define TEXT_TITLE_Y		(5)

#define TEXT_SCORE_X		(35)

#define TEXT_FIRST_X		(TEXT_TITLE_X)
#define TEXT_FIRST_Y		(TEXT_TITLE_Y + 20)

#define TEXT_SECOND_X		(TEXT_TITLE_X)
#define TEXT_SECOND_Y		(TEXT_TITLE_Y + 30)

#define TEXT_THIRD_X		(TEXT_TITLE_X)
#define TEXT_THIRD_Y		(TEXT_TITLE_Y + 40)

    view_render.clear();

    view_render.setTextSize(1);
    view_render.setTextColor(WHITE);
    view_render.setCursor(TEXT_TITLE_X, TEXT_TITLE_Y);
    view_render.print("Highscore");

    view_render.setCursor(TEXT_FIRST_X, TEXT_FIRST_Y);
    view_render.print("1. ");
    view_render.setCursor(TEXT_SCORE_X, TEXT_FIRST_Y);
    view_render.print(sst_game_score.first_place);

    view_render.setCursor(TEXT_SECOND_X, TEXT_SECOND_Y);
    view_render.print("2. ");
    view_render.setCursor(TEXT_SCORE_X, TEXT_SECOND_Y);
    view_render.print(sst_game_score.second_place);

    view_render.setCursor(TEXT_THIRD_X, TEXT_THIRD_Y);
    view_render.print("3. ");
    view_render.setCursor(TEXT_SCORE_X, TEXT_THIRD_Y);
    view_render.print(sst_game_score.third_place);
}

void sst_score_sort()
{
    if (sst_game_score.current_score > sst_game_score.first_place)
    {
        sst_game_score.third_place = sst_game_score.second_place;
        sst_game_score.second_place = sst_game_score.first_place;
        sst_game_score.first_place = sst_game_score.current_score;
    }
    else if (sst_game_score.current_score > sst_game_score.second_place)
    {
        sst_game_score.third_place = sst_game_score.second_place;
        sst_game_score.second_place = sst_game_score.current_score;
    }
    else if (sst_game_score.current_score > sst_game_score.third_place)
    {
        sst_game_score.third_place = sst_game_score.current_score;
    }
}

void sst_game_highscore_handler(ak_msg_t* msg)
{
    switch (msg->sig)
    {
    case SCREEN_ENTRY:
    {
        APP_DBG_SIG("SCREEN_HIGHSCORE_ENTRY\n");
        view_render.initialize();
        view_render_display_on();

        sst_score_sort();

        timer_set(AC_TASK_DISPLAY_ID, AC_DISPLAY_SHOW_IDLE, AC_DISPLAY_IDLE_INTERVAL, TIMER_ONE_SHOT);
    }
    break;

    case AC_DISPLAY_BUTTON_UP_LONG_PRESSED:
    {
        APP_DBG_SIG("HIGH_SCORE_RESET\n");
        sst_game_score.first_place = 0;
        sst_game_score.second_place = 0;
        sst_game_score.third_place = 0;
    }
    break;

    case AC_DISPLAY_BUTTON_MODE_RELEASED:
    {
        APP_DBG_SIG("OUT_HIGH_SCORE\n");
        SCREEN_TRAN(sst_game_menu_handler, &sst_game_menu);
    }
    break;

    case AC_DISPLAY_SHOW_IDLE:
    {
        SCREEN_TRAN(sst_game_idle_handler, &sst_game_idle);
    }
    default:
        break;
    }
}
