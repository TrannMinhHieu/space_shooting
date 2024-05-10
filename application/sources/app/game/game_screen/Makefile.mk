CFLAGS		+= -I./sources/app/game/game_libraries/game_scr_lib
CPPFLAGS	+= -I./sources/app/game/game_libraries/game_scr_lib

VPATH += sources/app/game/game_screen
VPATH += sources/app/game/game_screen/game_screen_other

# CPP source files
SOURCES_CPP += sources/app/game/game_screen/sst_game_screen_main.cpp
SOURCES_CPP += sources/app/game/game_screen/sst_game_menu.cpp
SOURCES_CPP += sources/app/game/game_screen/sst_game_bitmap.cpp
SOURCES_CPP += sources/app/game/game_screen/sst_game_highscore.cpp

SOURCES_CPP += sources/app/game/game_screen/game_screen_other/sst_game_startup.cpp
SOURCES_CPP += sources/app/game/game_screen/game_screen_other/sst_game_idle.cpp