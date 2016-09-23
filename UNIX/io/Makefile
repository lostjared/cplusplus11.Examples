CXX_FLAGS=-std=c++11

all: read-test rdwr-test redir-test
	
rdwr-test: io-readwrite.cpp
	$(CXX) $(CXX_FLAGS) io-readwrite.cpp -o rdwr-test

read-test: io-read.cpp
	$(CXX) $(CXX_FLAGS) io-read.cpp -o read-test

redir-test: io-redirect.cpp
	$(CXX) $(CXX_FLAGS) io-redirect.cpp -o redir-test

clean:
	rm -f read-test rdwr-test redir-test

