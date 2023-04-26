all: build launch clean

build: compile link

compile:
	g++ -Isrc/include -c code/*.cpp

link:
	g++ *.o -o main -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system

launch:
	./main.exe

clean:
	del main.o
	del main.exe