CXX = g++
CXXFLAGS = -Wall -MMD
EXEC = cc3k
OBJECTS = main.o grid.o board.o cell.o character.o player.o human.o dwarf.o orc.o elve.o enemy.o vampire.o werewolf.o troll.o phoenix.o merchant.o dragon.o goblin.o printfile.o item.o room.o

DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lcurses

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
