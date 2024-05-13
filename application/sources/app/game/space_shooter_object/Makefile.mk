CFLAGS		+= -I./sources/app/game/game_libraries/game_obj_lib
CPPFLAGS	+= -I./sources/app/game/game_libraries/game_obj_lib

VPATH += sources/app/game/space_shooter_object

# CPP source files
SOURCES_CPP += sources/app/game/space_shooter_object/sst_player_ship.cpp
SOURCES_CPP += sources/app/game/space_shooter_object/sst_player_missile.cpp

SOURCES_CPP += sources/app/game/space_shooter_object/sst_enemy_ship.cpp
SOURCES_CPP += sources/app/game/space_shooter_object/sst_enemy_missile.cpp

SOURCES_CPP += sources/app/game/space_shooter_object/sst_asteroid.cpp
SOURCES_CPP += sources/app/game/space_shooter_object/sst_explosion.cpp
SOURCES_CPP += sources/app/game/space_shooter_object/terrain.cpp