all: compile link

compile:
	g++ -c main.cpp
	g++ -c cell.cpp
	
# add -mwindows at end of link to hide console
link:
	g++ main.o cell.o -o main -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system -lfreetype
