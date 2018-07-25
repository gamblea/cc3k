# Makefile
CXX=g++
CXXFLAGS=-std=c++14 -Wextra -Wpedantic -Wall -MMD -g -Werror=vla
OBJECTS=cck.o Character.o Direction.o CharacterStats.o Command.o Error.o Event.o Game.o GameConfig.o GameIO.o Helpers.o Item.o Level.o Map.o Player.o Position.o Potion.o PotionEffects.o resource.o Sprite.o Stairs.o TextDisplay.o Treasure.o TreasureStats.o 
DEPENDS=${OBJECTS:.o=.d}
EXEC=cck

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${DEPENDS} ${EXEC}
.PHONY: clean
