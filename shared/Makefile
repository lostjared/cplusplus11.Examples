
CXXFLAGS=-Wall -std=c++11 

all: sharedtest sharedtest2

sharedtest: sharedtest.cpp
	$(CXX) sharedtest.cpp -o sharedtest $(CXXFLAGS)
sharedtest2: sharedtest2.cpp
	$(CXX) sharedtest2.cpp -o sharedtest2 $(CXXFLAGS)
clean:
	rm -f sharedtest sharedtest2
