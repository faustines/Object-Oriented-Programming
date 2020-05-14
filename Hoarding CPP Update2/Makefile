hoarding.out: main.o main.o boardHandler.o csvHandler.o gameStateHandler.o inputHandler.o playerHandler.o diceHandler.o rulesHandler.o space.o goSpace.o propertySpace.o jailSpace.o gotojailSpace.o freeparkingSpace.o paybankSpace.o
	g++ -O0 -Wall -Werror -Wno-unused-result -o hoarding.out main.o boardHandler.o csvHandler.o gameStateHandler.o inputHandler.o playerHandler.o diceHandler.o rulesHandler.o space.o goSpace.o propertySpace.o jailSpace.o gotojailSpace.o freeparkingSpace.o paybankSpace.o
 -std=c++14

main.o: main.cpp gameStateHandler.h
	g++ -g -O0 -Wall -Werror -Wno-unused-result -c main.cpp -std=c++14

boardHandler.o: boardHandler.cpp boardHandler.h space.h csvHandler.h propertySpace.h goSpace.h jailSpace.h gotojailSpace.h paybankSpace.h freeparkingSpace.h playerHandler.h inputHandler.h
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

space.o: space.cpp space.h rulesHandler.h
	g++ -g -O0 -Wall -Werror -Wno-unused-result -c space.cpp -std=c++14

propertySpace.o: propertySpace.cpp propertySpace.h space.h rulesHandler.h playerHandler.h
	g++ -g -O0 -Wall -Werror -Wno-unused-result -c propertySpace.cpp -std=c++14

goSpace.o: goSpace.cpp goSpace.h space.h playerHandler.h
	g++ -g -O0 -Wall -Werror -Wno-unused-result -c goSpace.cpp -std=c++14

freeparkingSpace.o: freeparkingSpace.cpp freeparkingSpace.h space.h rulesHandler.h playerHandler.h
	g++ -g -O0 -Wall -Werror -Wno-unused-result -c freeparkingSpace.cpp -std=c++14

jailSpace.o: jailSpace.cpp jailSpace.h space.h rulesHandler.h playerHandler.h
	g++ -g -O0 -Wall -Werror -Wno-unused-result -c jailSpace.cpp -std=c++14

gotojailSpace.o: gotojailSpace.cpp gotojailSpace.h space.h rulesHandler.h playerHandler.h
	g++ -g -O0 -Wall -Werror -Wno-unused-result -c gotojailSpace.cpp -std=c++14

paybankSpace.o: paybankSpace.cpp paybankSpace.h space.h rulesHandler.h playerHandler.h
	g++ -g -O0 -Wall -Werror -Wno-unused-result -c paybankSpace.cpp -std=c++14

clean:
	rm -fr *.o *.out
