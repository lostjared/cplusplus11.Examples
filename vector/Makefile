CXX=c++
FLAGS=-std=c++11 

all: persist-test em-test

persist-test: persist_vector.cc
	$(CXX) -Wall $(FLAGS) persist_vector.cc -o persist-test
em-test: em.cc
	$(CXX) -Wall $(FLAGS) em.cc -o em-test 
clean:
	rm -f persist-test
	rm -f em-test
