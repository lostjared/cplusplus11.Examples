CXX=c++
FLAGS= -Wall -std=c++11  

all: time-test scoped-test looptest-test

time-test: timetest.cc
	$(CXX) timetest.cc -o time-test $(FLAGS)
scoped-test: scoped_t.cc
	$(CXX) scoped_t.cc -o scoped-test $(FLAGS)
looptest-test: looptest.cc
	$(CXX) looptest.cc -o looptest-test $(FLAGS)
clean:
	rm -f time-test scoped-test looptest-test
