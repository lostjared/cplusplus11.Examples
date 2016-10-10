
FLAGS=-std=c++11  -Wall
all: init-test init-test2

init-test: init_list.cc
	$(CXX) init_list.cc -o init-test $(FLAGS)
init-test2: init_test.cpp
	$(CXX) init_test.cpp -o init-test2 $(FLAGS)
clean:
	rm -f init-test init-test2
