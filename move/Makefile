CXX=c++
FLAGS= -O2 -Wall -std=c++11  

all: movet move-test2 move-test3

movet: move_test.cc
	$(CXX) move_test.cc -o movet $(FLAGS)
move-test2: move_test2.cc
	$(CXX) move_test2.cc -o move-test2 $(FLAGS)
move-test3: move_test3.cc
	$(CXX) move_test3.cc -o move-test3 $(FLAGS)
clean:
	rm -f movet move-test2 move-test3
