
CXXFLAGS=-Wall -std=c++11  

all: it-test it-test2 it-test3

it-test: it.cpp
	$(CXX) it.cpp -o it-test $(CXXFLAGS)
it-test2: it2.cpp
	$(CXX) it2.cpp -o it-test2 $(CXXFLAGS)
it-test3: it3.cpp
	$(CXX) it3.cpp -o it-test3 $(CXXFLAGS)
clean:
	rm -f it-test it-test2 it-test3
