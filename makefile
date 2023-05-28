CXX = g++
CXX_FLAGS = -Wall -Wextra -Werror -pedantic -std=c++17
SRC_DIR = code
TEST_DIR = tests

all: build launch clean

build: compile link

compile:
	${CXX} ${CXX_FLAGS} -IExtLibs/include -c code/*.cpp

link:
	${CXX} ${CXX_FLAGS} *.o -o carbrawl -LExtLibs/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

launch:
	./carbrawl

clean:
	rm *.o
	rm *.exe