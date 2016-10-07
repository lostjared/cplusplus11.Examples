CXX=c++
FLAGS= -Wall -std=c++11 

all: ar-test ar2-test

ar-test: ar.cc
	$(CXX) $(FLAGS) ar.cc -o ar-test 
ar2-test: ar2.cc
	$(CXX) $(FLAGS) ar2.cc -o ar2-test
clean:
	rm -f ar-test ar2-test
