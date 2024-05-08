CFLAGS		+= -I./sources/app/game/game_libraries/game_scr_lib
CPPFLAGS	+= -I./sources/app/game/game_libraries/game_scr_lib

VPATH += sources/app/game/game_screen

# CPP source files
SOURCES_CPP += sources/app/game/game_screen/sst_game_screen_main.cpp
SOURCES_CPP += sources/app/game/game_screen/sst_game_menu.cpp
SOURCES_CPP += sources/app/game/game_screen/sst_game_bitmap.cpp
SOURCES_CPP += sources/app/game/game_screen/sst_game_highscore.cpp
