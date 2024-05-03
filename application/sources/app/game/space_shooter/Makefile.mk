CFLAGS		+= -I./sources/app/game/space_shooter
CPPFLAGS	+= -I./sources/app/game/space_shooter

VPATH += sources/app/game/space_shooter

# CPP source files
SOURCES_CPP += sources/app/game/space_shooter/ship_player.cpp
SOURCES_CPP += sources/app/game/space_shooter/ship_enemy.cpp
SOURCES_CPP += sources/app/game/space_shooter/missile.cpp
SOURCES_CPP += sources/app/game/space_shooter/asteroid.cpp
SOURCES_CPP += sources/app/game/space_shooter/explosion.cpp
