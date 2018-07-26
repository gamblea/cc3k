# Makefile
CXX=g++
CXXFLAGS=-std=c++14 -Wextra -Wpedantic -Wall -MMD -g -Werror=vla
OBJECTS=cck.o Character.o CharacterStats.o Command.o Errors.o Event.o Game.o GameConfig.o GameIO.o Helpers.o Item.o Level.o Map.o Player.o Position.o Potion.o PotionEffects.o Sprite.o Stairs.o  Treasure.o TreasureStats.o Room.o SpriteFactory.o Dragon.o
DEPENDS=${OBJECTS:.o=.d}
EXEC=cc3k

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${DEPENDS} ${EXEC}
.PHONY: clean
