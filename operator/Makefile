FLAGS= -std=c++11 -Wall
all: operator-test delete-test plus-test equal-test

operator-test:
	$(CXX) -Wall  operator.cc -o operator-test -std=c++11
delete-test: default.cc 
	$(CXX) -Wall default.cc -o delete-test -std=c++11 
plus-test: plus.cc
	$(CXX) -Wall plus.cc -o plus-test -std=c++11 
equal-test: equal.cpp
	$(CXX) $(FLAGS) equal.cpp -o equal-test 
clean:
	rm -f operator-test delete-test plus-test equal-test
