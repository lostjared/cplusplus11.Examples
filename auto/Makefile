CXX=c++
CXX_FLAGS= -std=c++11
all: auto-test auto-test2

auto-test: autotest.cc
	$(CXX) $(CXX_FLAGS)  autotest.cc -o auto-test
auto-test2: autotest2.cpp
	$(CXX) $(CXX_FLAGS)  autotest2.cpp -o auto-test2  
clean:
	rm -f auto-test auto-test2
