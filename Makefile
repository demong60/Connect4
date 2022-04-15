output: Main.o Game.o Util.o Algorithms.o Node.o
	g++ -Ofast Game.o Main.o Util.o Node.o Algorithms.o -Wall -o out

Main.o: Main.cpp
	g++ -Ofast -c Main.cpp

Game.o: Game.cpp Game.h
	g++ -Ofast -c Game.cpp 

Util.o: Util.cpp Util.h
	g++ -Ofast -c Util.cpp

Node.o: Node.cpp Node.h
	g++ -Ofast -c Node.cpp

Algorithms.o: Algorithms.cpp Algorithms.h
	g++ -Ofast -c Algorithms.cpp

clean:
	rm *.o out