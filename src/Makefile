CC=g++

FLAGS=-std=c++14 -Wall

all: map visual regionFinder clean

map: NET-ASAR-map.o auxFunc.o modelClass.o
	$(CC) $(FLAGS) NET-ASAR-map.o auxFunc.o modelClass.o -o NET-ASAR-map

NET-ASAR-map.o: NET-ASAR-map.cpp
	$(CC) $(FLAGS) -c NET-ASAR-map.cpp

auxFunc.o: auxFunc.cpp auxFunc.h
	$(CC) $(FLAGS) -c auxFunc.cpp

modelClass.o: modelClass.cpp modelClass.h
	$(CC) $(FLAGS) -c modelClass.cpp

visual: NET-ASAR-visual.cpp
	$(CC) $(FLAGS) NET-ASAR-visual.cpp -o NET-ASAR-visual

regionFinder: NET-ASAR-regionFinder.cpp
	$(CC) $(FLAGS) NET-ASAR-regionFinder.cpp -o NET-ASAR-regionFinder

clean:
	rm *.o
