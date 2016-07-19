MAIN_SOURCE=main.cpp
STRING_TEST=string-test.cpp
MOVE_TEST=movetest.cpp
LOOP_TEST=looptest.cpp
READ_TEST=readtest.cpp
CXXFLAGS= -std=c++11 

all:
	$(CXX) $(CXXFLAGS) $(MAIN_SOURCE) -o stopwatch-test
	$(CXX) $(CXXFLAGS) $(STRING_TEST) -o stopwatch-string
	$(CXX) $(CXXFLAGS) $(MOVE_TEST) -o stopwatch-move
	$(CXX) $(CXXFLAGS) $(LOOP_TEST) -o loop-test
	$(CXX) $(CXXFLAGS) $(READ_TEST) -o read-test

clean:
	rm -f stopwatch-test stopwatch-string stopwatch-move loop-test
