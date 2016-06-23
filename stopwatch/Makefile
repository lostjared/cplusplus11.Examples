MAIN_SOURCE=main.cpp
STRING_TEST=string-test.cpp
MOVE_TEST=movetest.cpp

CXXFLAGS= -std=c++11 

all:
	$(CXX) $(CXXFLAGS) $(MAIN_SOURCE) -o stopwatch-test
	$(CXX) $(CXXFLAGS) $(STRING_TEST) -o stopwatch-string
	$(CXX) $(CXXFLAGS) $(MOVE_TEST) -o stopwatch-move
clean:
	rm -f stopwatch-test stopwatch-string
