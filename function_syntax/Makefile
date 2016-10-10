

all: func-test func-test1
func-test: function_syntax.cc
	$(CXX)  -Wall function_syntax.cc -o func-test -std=c++11
func-test1: test1.cc  
	$(CXX)  -Wall test1.cc -o func-test1 -std=c++11
clean:
	rm -f func-test1 func-test
