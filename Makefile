CXX = g++
CXXFLAGS = -std=c++14 -g -Wall -MMD -Werror=vla -fpermissive
OBJECTS = main.o board.o edge.o tile.o vertice.o road.o builderId.o tileType.o \
          resourceType.o builder.o housing.o housingType.o view.o persistence.o \
          gameFactory.o game.o gameController.o loadedDice.o fairDice.o \
          beginningOfGame.o beginningOfTurn.o duringTheTurn.o endOfGame.o \
          gameRule.o exceptions.o random.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = constructor

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

clean :
	rm ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS} # reads the .d files and reruns dependencies

