all: main.o
	g++ main.cpp -o main.o

debug: main.o
	g++ main.cpp -sg -o main.o

main.o: main.cpp
	g++ main.cpp -o main.o
