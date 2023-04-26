all: compile link

compile:
	g++ -Isrc/include -c code/*.cpp

link:
	g++ main.o -o main -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system

clean:
	del main.o 
	del main.exe