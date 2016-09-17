CXX_FLAGS=-std=c++11

all: read-test rdwr-test
	
rdwr-test: io-readwrite.cpp
	$(CXX) $(CXX_FLAGS) io-readwrite.cpp -o rdwr-test

read-test: io-read.cpp
	$(CXX) $(CXX_FLAGS) io-read.cpp -o read-test


clean:
	rm -f read-test rdwr-test

