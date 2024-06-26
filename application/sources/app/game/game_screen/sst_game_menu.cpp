#include "sst_game_menu.h"

#define ITEM_SPACING (20)
#define NUM_OF_ITEMS (3)
#define NUM_OF_ITEMS_ON_SCREEN (3)
#define MENU_SCREEN_VISIBLE_HEIGHT (60)

struct sst_menu_items
{
    unsigned int item_1 : 1;
    unsigned int item_2 : 1;
    unsigned int item_3 : 1;
};

static char sst_menu_items_name[NUM_OF_ITEMS][15] =
    {
        "START",      // item_1
        "HIGH SCORE", // item_2
        "EXIT",       // item_3
};

enum sst_switchToItems_e {
    START,
    HIGH_SCORE,
    EXIT,
};

typedef struct
{
    int screen;
    int location;
} sst_screen_display_t;

union sst_menu_screen
{
    uint32_t _id = 1;
    sst_menu_items menu_items_id;
};

typedef struct
{
    uint8_t axis_x = 0;
    uint8_t axis_y = 0;
    uint8_t size_w = 123;
    uint8_t size_h = 20;
    uint8_t size_r = 3;
} sst_menu_display_frame_t;

sst_screen_display_t screen_menu;
sst_menu_display_frame_t display_frame;
sst_menu_display_frame_t frame[3];

static void sst_menu_render();

view_dynamic_t dyn_view_game_menu = {
    {
        .item_type = ITEM_TYPE_DYNAMIC,
    },
    sst_menu_render};

view_screen_t sst_game_menu = {
    &dyn_view_game_menu,
    ITEM_NULL,
    ITEM_NULL,

    .focus_item = 0,
};


void sst_menu_render()
{
#define GAME_MENU_TEXT_SPACING_X_AXIS (10)

    view_render.setTextSize(1);
    for (uint8_t i = 0; i < NUM_OF_ITEMS_ON_SCREEN; i++)
    {
        view_render.setCursor(GAME_MENU_TEXT_SPACING_X_AXIS, i * ITEM_SPACING);
        view_render.drawFastVLine(display_frame.axis_x + 2, display_frame.axis_y + 4, 10, WHITE);

        view_render.setCursor(GAME_MENU_TEXT_SPACING_X_AXIS, i * ITEM_SPACING + 6);
        view_render.print(sst_menu_items_name[screen_menu.screen + i]);
    }
}

void sst_menu_cursor()
{
    display_frame.axis_y = frame[screen_menu.location - screen_menu.screen].axis_y;
    frame[0].axis_y = 0;
    frame[1].axis_y = 20;
    frame[2].axis_y = 40;
}

void sst_menu_cursor_focus()
{
    switch (screen_menu.location)
    {
    case START:
        SCREEN_TRAN(sst_game_play_handler, &sst_game_screen);
        break;
    case HIGH_SCORE:
        SCREEN_TRAN(sst_game_highscore_handler, &sst_game_highscore);
        break;
    case EXIT:
        SCREEN_TRAN(sst_game_idle_handler, &sst_game_idle);
        break;
    default:
        break;
    }
}

void sst_game_menu_handler(ak_msg_t* msg)
{
    switch (msg->sig)
    {
    case SCREEN_ENTRY:
    {
        APP_DBG_SIG("SCREEN_MENU_ENTRY\n");
        view_render.initialize();
        view_render_display_on();
        sst_menu_cursor();
        timer_set(AC_TASK_DISPLAY_ID, AC_DISPLAY_SHOW_IDLE, AC_DISPLAY_IDLE_INTERVAL, TIMER_ONE_SHOT);
    }
    break;

    case AC_DISPLAY_SHOW_IDLE:
    {
        SCREEN_TRAN(sst_game_idle_handler, &sst_game_idle);
    }
    break;

    case AC_DISPLAY_BUTTON_MODE_RELEASED:
    {
        sst_menu_cursor_focus();
    }
    break;

    case AC_DISPLAY_BUTTON_UP_RELEASED:
    {
        if (screen_menu.location > 0)
        {
            screen_menu.location--;
        }
        if (display_frame.axis_y == frame[0].axis_y)
        {
            if (screen_menu.screen > 0)
            {
                screen_menu.screen--;
            }
        }
        else if (display_frame.axis_y == frame[1].axis_y)
        {
            display_frame.axis_y = frame[0].axis_y;
        }
        else if (display_frame.axis_y == frame[2].axis_y)
        {
            display_frame.axis_y = frame[1].axis_y;
        }
        sst_menu_cursor();

        timer_set(AC_TASK_DISPLAY_ID, AC_DISPLAY_SHOW_IDLE, AC_DISPLAY_IDLE_INTERVAL, TIMER_ONE_SHOT);
    }
    break;

    case AC_DISPLAY_BUTTON_DOWN_RELEASED:
    {
        if (screen_menu.location < NUM_OF_ITEMS - 1)
        {
            screen_menu.location++;
        }
        if (display_frame.axis_y == frame[0].axis_y)
        {
            display_frame.axis_y = frame[1].axis_y;
        }
        else if (display_frame.axis_y == frame[1].axis_y)
        {
            display_frame.axis_y = frame[2].axis_y;
        }
        else if (display_frame.axis_y == frame[2].axis_y)
        {
            if (screen_menu.screen < NUM_OF_ITEMS - NUM_OF_ITEMS_ON_SCREEN)
            {
                screen_menu.screen++;
            }
        }
        sst_menu_cursor();

        timer_set(AC_TASK_DISPLAY_ID, AC_DISPLAY_SHOW_IDLE, AC_DISPLAY_IDLE_INTERVAL, TIMER_ONE_SHOT);
    }
    break;

    default:
        break;
    }
}