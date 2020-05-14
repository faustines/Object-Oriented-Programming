hoarding.out: main.o Board.o GameState.o Move.o Player.o Property.o PropertyManager.o PropertySet.o Rules.o Space.o Utility.o
	gcc -g -Wall -Werror -o hoarding.out main.o Board.o GameState.o Move.o Player.o Property.o PropertyManager.o PropertySet.o Rules.o Space.o Utility.o

main.o: main.c GameState.h Move.h
	gcc -g -Wall -Werror -c main.c

Board.o: Board.c Board.h Utility.h
		gcc -g -Wall -Werror -c Board.c

GameState.o: GameState.c GameState.h Utility.h
		gcc -g -Wall -Werror -c GameState.c

Move.o: Move.c Move.h GameState.h
	gcc -g -Wall -Werror -c Move.c

Player.o: Player.c Player.h GameState.h
	gcc -g -Wall -Werror -c Player.c 

Property.o: Property.c Property.h 
	gcc -g -Wall -Werror -c Property.c

PropertyManager.o: PropertyManager.c PropertyManager.h Utility.h
	gcc -g -Wall -Werror -c PropertyManager.c

PropertySet.o: PropertySet.c PropertySet.h
	gcc -g -Wall -Werror -c PropertySet.c

Rules.o: Rules.c Rules.h Utility.h
	gcc -g -Wall -Werror -c Rules.c

Space.o: Space.c Space.h Utility.h
	gcc -g -Wall -Werror -c Space.c

Utility.o: Utility.c Utility.h
	gcc -g -Wall -Werror -c Utility.c

clean:
	rm *.out *.o