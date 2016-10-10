CXX=c++
FLAGS= -std=c++11  -Wall
all: enum-test ec-test

enum-test: enum.cc
	$(CXX)  enum.cc -o enum-test $(FLAGS)
ec-test: enum_class.cpp
	$(CXX) enum_class.cpp -o ec-test $(FLAGS)
clean: 
	rm -f enum-test ec-test
