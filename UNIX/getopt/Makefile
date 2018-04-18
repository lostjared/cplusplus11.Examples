CXX_FLAGS=-std=c++11

all: getopt-test getopt-test2

getopt-test: getopt.cpp
	$(CXX) $(CXX_FLAGS) getopt.cpp -o getopt-test
getopt-test2: getopt2.cpp
	$(CXX) $(CXX_FLAGS) getopt2.cpp -o getopt-test2
clean:
	rm -f getopt-test getopt-test2
