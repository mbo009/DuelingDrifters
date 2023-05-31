CXX = g++
CXX_FLAGS = -Wall -Wextra -Werror -pedantic -std=c++17
SRC_DIR = code
TEST_DIR = tests

all: build launch clean

build: compile link

compile:
	${CXX} ${CXX_FLAGS} -IExtLibs/include -c code/*.cpp

link:
	${CXX} ${CXX_FLAGS} *.o -o DuelingDrifters -LExtLibs/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

launch:
	./DuelingDrifters

test_main:
	$(CXX) $(CXX_FLAGS) $(TEST_DIR)/test_main.cpp -c

test_carObj:
	$(CXX) $(CXX_FLAGS) $(SRC_DIR)/carObj.cpp $(TEST_DIR)/test_carObj.cpp -o TestCarObj 
	./TestCarObj --success

clean:
	del *.o
	del *.exe