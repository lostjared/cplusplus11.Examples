
FLAGS= -Wall -std=c++11 

all: typeid-test typeid-test2

typeid-test: typeid_test.cc
	$(CXX) typeid_test.cc -o typeid-test $(FLAGS)
typeid-test2: typeid_test2.cpp
	$(CXX) typeid_test2.cpp -o typeid-test2 $(FLAGS)
clean:
	rm -f typeid-test typeid-test2
