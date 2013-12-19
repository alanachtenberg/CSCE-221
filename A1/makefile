all: main.o
	g++-4.7 -std=c++11  main.o -o main
main.o: main.cpp question.h
	g++-4.7 -std=c++11 -c main.cpp
clean:
	rm *.o main
