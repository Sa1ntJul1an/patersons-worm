all: compile link

compile:
	g++ -c main.cpp
	g++ -c cell.cpp
	g++ -c node.cpp
	g++ -c worm.cpp
	g++ -c environment.cpp
	g++ -c directionUtils.cpp

# add -mwindows at end of link to hide console
link:
	g++ main.o cell.o node.o worm.o environment.o directionUtils.o -o main -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system -lfreetype
