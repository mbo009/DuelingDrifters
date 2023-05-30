CXX = g++
CXX_FLAGS = -Wall -Wextra -Werror -pedantic -std=c++17
SRC_DIR = code
TEST_DIR = tests

all: build launch

build: compile link

compile:
	${CXX} ${CXX_FLAGS} -IExtLibs/include -c code/*.cpp

link:
	${CXX} ${CXX_FLAGS} *.o -o carbrawl -LExtLibs/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

launch:
	./carbrawl

test_main:
	$(CXX) $(CXX_FLAGS) $(TEST_DIR)/test_main.cpp -c

test_carObj:
	$(CXX) $(CXX_FLAGS) test_carObj.o  $(SRC_DIR)*.cpp $(TEST_DIR)/test_carObj.cpp -o TestCarObj && ./TestCarObj --success

clean:
	rm *.o
	rm *.exe