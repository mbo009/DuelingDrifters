all: build launch clean

build: compile link

compile:
	g++ -Isrc/include -c code/*.cpp

link:
	g++ *.o -o main -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

launch:
	./main.exe

clean:
	del *.o
	del *.exe