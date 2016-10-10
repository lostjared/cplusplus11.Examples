CFLAGS=-std=c++11
all: persist-test persist-vec-test

persist-test: persist.cc
	$(CXX) $(CFLAGS) -Wall persist.cc -o persist-test
persist-vec-test: persist-vector-main.cpp 
	$(CXX) $(CFLAGS) persist-vector-main.cpp -o persist-vec-test 
clean:
	rm -f persist-test persist-vec-test
