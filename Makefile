OBJS = main.o Agent.o Circle.o Flock.o Game.o Parameter.o PVector.o Triangle.o
CC = g++
STD = -std=c++17
SFML = -lsfml-graphics -lsfml-window -lsfml-system

all : main clean

main : $(OBJS)
	$(CC) $(STD) -o main $(OBJS) $(SFML)
main.o : main.cpp
	$(CC) $(STD) -c main.cpp
Agent.o : Agent.cpp
	$(CC) $(STD) -c Agent.cpp
Circle.o : Circle.cpp
	$(CC) $(STD) -c Circle.cpp
Flock.o : Flock.cpp
	$(CC) $(STD) -c Flock.cpp
Game.o : Game.cpp
	$(CC) $(STD) -c Game.cpp
Parameter.o : Parameter.cpp
	$(CC) $(STD) -c Parameter.cpp
PVector.o : PVector.cpp
	$(CC) $(STD) -c PVector.cpp
Triangle.o : Triangle.cpp
	$(CC) $(STD) -c Triangle.cpp
clean :
	rm *.o