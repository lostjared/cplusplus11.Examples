CXX=c++
FLAGS= -std=c++11 -Wall
all:
	$(CXX) -Wall  operator.cc -o operator-test -std=c++11 
	$(CXX) -Wall default.cc -o delete-test -std=c++11 
	$(CXX) -Wall plus.cc -o plus-test -std=c++11 
	$(CXX) $(FLAGS) equal.cpp -o equal-test 
clean:
	rm -f operator-test delete-test plus-test equal-test
