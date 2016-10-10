CXX_FLAGS= -std=c++11 

all: static1-test static2-test

static1-test: static1.cpp
	$(CXX) $(CXX_FLAGS) static1.cpp -o static1-test
static2-test: static2.cpp
	$(CXX) $(CXX_FLAGS) static2.cpp -o static2-test 
clean:
	rm -f static1-test static2-test
