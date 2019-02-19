all: particles main

particles: particles.o
	g++ particles.o -o particles -lsfml-graphics -lsfml-window -lsfml-system	

main: main.o
	g++ main.o -o main -lsfml-graphics -lsfml-window -lsfml-system	

main.o: main.cc
	g++ -c main.cc

particles.o: particles.cc
	g++ -c particles.cc