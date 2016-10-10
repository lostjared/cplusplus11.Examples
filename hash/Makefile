
CXX_FLAGS=-std=c++11   -Wall

all: hash1-test hash2-test hash3-test

hash1-test: hash1.cpp
	$(CXX) hash1.cpp -o hash1-test $(CXX_FLAGS)
hash2-test: hash2.cpp
	$(CXX) hash2.cpp -o hash2-test $(CXX_FLAGS)
hash3-test: hash3.cpp
	$(CXX) hash3.cpp -o hash3-test $(CXX_FLAGS)

clean:
	rm -f hash1-test hash2-test hash3-test
