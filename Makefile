all: main

main: main.o
	g++ main.o -o main -lsfml-graphics -lsfml-window -lsfml-system	

main.o: main.cc
	g++ -c main.cc

clean:
	rm *.o