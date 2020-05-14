hoarding.out: main.o main.o boardHandler.o csvHandler.o gameStateHandler.o inputHandler.o playerHandler.o diceHandler.o rulesHandler.o spaceClasses.o spaceHandler.o
	g++ -O0 -Wall -Werror -Wno-unused-result -o hoarding.out main.o boardHandler.o csvHandler.o gameStateHandler.o inputHandler.o playerHandler.o diceHandler.o rulesHandler.o spaceClasses.o spaceHandler.o -std=c++14

main.o: main.cpp gameStateHandler.h
	g++ -g -O0 -Wall -Werror -Wno-unused-result -c main.cpp -std=c++14

boardHandler.o: boardHandler.cpp boardHandler.h spaceHandler.h csvHandler.h spaceClasses.h playerHandler.h spaceHandler.h
	g++ -g -O0 -Wall -Werror -Wno-unused-result -c boardHandler.cpp -std=c++14

csvHandler.o: csvHandler.cpp csvHandler.h
	g++ -g -O0 -Wall -Werror -Wno-unused-result -c csvHandler.cpp -std=c++14

gameStateHandler.o: gameStateHandler.cpp gameStateHandler.h boardHandler.h rulesHandler.h diceHandler.h inputHandler.h
	g++ -g -O0 -Wall -Werror -Wno-unused-result -c gameStateHandler.cpp -std=c++14

inputHandler.o: inputHandler.cpp inputHandler.h playerHandler.h
	g++ -g -O0 -Wall -Werror -Wno-unused-result -c inputHandler.cpp -std=c++14

playerHandler.o: playerHandler.cpp playerHandler.h boardHandler.h
	g++ -g -O0 -Wall -Werror -Wno-unused-result -c playerHandler.cpp -std=c++14

diceHandler.o: diceHandler.cpp diceHandler.h
	g++ -g -O0 -Wall -Werror -Wno-unused-result -c diceHandler.cpp -std=c++14

rulesHandler.o: rulesHandler.cpp rulesHandler.h
	g++ -g -O0 -Wall -Werror -Wno-unused-result -c rulesHandler.cpp -std=c++14

spaceClasses.o: spaceClasses.cpp spaceClasses.h playerHandler.h spaceHandler.h
	g++ -g -O0 -Wall -Werror -Wno-unused-result -c spaceClasses.cpp -std=c++14

spaceHandler.o: spaceHandler.cpp spaceHandler.h
	g++ -g -O0 -Wall -Werror -Wno-unused-result -c spaceHandler.cpp -std=c++14

clean:
	rm -fr *.o *.out
