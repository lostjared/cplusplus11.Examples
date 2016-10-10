FLAGS=-Wall -std=c++11  

all: namespace-test namespace-test2 namespace-test3

namespace-test: inline_namespace_ex.cc
	$(CXX) inline_namespace_ex.cc -o namespace-test $(FLAGS)
namespace-test2: namespace2.cpp
	$(CXX) namespace2.cpp -o namespace-test2 $(FLAGS)
namespace-test3: namespace3.cpp
	$(CXX) namespace3.cpp -o namespace-test3 $(FLAGS)
clean:
	rm -rf namespace-test namespace-test2 namespace-test3
