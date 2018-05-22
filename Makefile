CXX=g++-5 -g
CXXFLAGS=-std=c++14 -Wall  -MMD -Werror=vla
EXEC=quadris
OBJECTS=block.o board.o cell.o centerblock.o commandInterpreter.o color.o graphicDisplay.o helper.o iblock.o jblock.o lblock.o level.o main.o oblock.o observer.o sblock.o score.o subject.o tblock.o textDisplay.o window.o zblock.o 
DEPENDS=${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

.PHONY: clean
clean:
	rm ${OBJECTS} ${DEPENDS} 
