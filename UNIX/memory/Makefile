CXX_FLAGS= -std=c++11

all: alloca-test memory-test realloc-test


alloca-test: alloca-test.cpp
	$(CXX) $(CXX_FLAGS) alloca-test.cpp -o alloca-test
memory-test: memory.cpp
	$(CXX) $(CXX_FLAGS) memory.cpp -o memory-test
realloc-test: realloc.cpp
	$(CXX) $(CXX_FLAGS) realloc.cpp -o realloc-test

clean:
	rm -f alloca-test memory-test realloc-test
