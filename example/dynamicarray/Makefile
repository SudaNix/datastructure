CXX := g++
BIN := bin

main: main.o 
	g++ -Wall main.o -L../../lib -lds

main.o: main.cpp
	g++ -Wall -c -ggdb main.cpp 

clean:
	rm *.o a.out

