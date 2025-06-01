all: compile link

compile:
	g++ -c main.cpp
	g++ -c cell.cpp
	g++ -c search.cpp
	g++ -c searchFactory.cpp
	g++ -c breadthFirst.cpp
	g++ -c depthFirst.cpp
	g++ -c aStar.cpp
	
# add -mwindows at end of link to hide console
link:
	g++ main.o cell.o search.o searchFactory.o breadthFirst.o depthFirst.o aStar.o -o main -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system -lfreetype
