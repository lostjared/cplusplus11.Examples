CXX_FLAGS= -std=c++11
all: unique-test smart-test

unique-test: unique.cc
	$(CXX) $(CXX_FLAGS) -Wall  unique.cc -o unique-test 
smart-test: smart.cpp
	$(CXX) $(CXX_FLAGS)  smart.cpp -o smart-test
clean:
	rm -f unique-test smart-test
