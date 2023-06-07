# Command using in makefile is for Windows OS only

CXX = g++
CXX_FLAGS = -Wall -Wextra -Werror -pedantic -std=c++17
SFML_LIB = ExtLibs/lib
SFML_INCLUDE = ExtLibs/include
SRC_DIR = code/
TEST_DIR = tests/

all: release clean launch

build: compile link

compile:
	$(CXX) $(CXX_FLAGS) -I$(SFML_INCLUDE) -c $(SRC_DIR)*.cpp

link:
	$(CXX) $(CXX_FLAGS) *.o -o DuelingDrifters -L$(SFML_LIB) -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

release: build
	move DuelingDrifters.exe ./release/
	xcopy /E /I /Y assets release\assets

launch:
	./release/DuelingDrifters.exe

test_main: compile
	$(CXX) $(CXX_FLAGS) $(TEST_DIR)test_main.cpp -c

test_carObj:
	$(CXX) $(CXX_FLAGS) test_main.o carObj.o $(TEST_DIR)test_carObj.cpp -o TestCarObj
	./TestCarObj --success

clean:
	del *.o
	del *.exe