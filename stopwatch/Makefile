MAIN_SOURCE=main.cpp
STRING_TEST=string-test.cpp
MOVE_TEST=movetest.cpp
LOOP_TEST=looptest.cpp
READ_TEST=readtest.cpp
CXXFLAGS= -std=c++11 

all: stopwatch-test stopwatch-string stopwatch-move loop-test read-test

stopwatch-test: $(MAIN_SOURCE)
	$(CXX) $(CXXFLAGS) $(MAIN_SOURCE) -o stopwatch-test
stopwatch-string: $(STRING_TEST)
	$(CXX) $(CXXFLAGS) $(STRING_TEST) -o stopwatch-string
stopwatch-move: $(MOVE_TEST)
	$(CXX) $(CXXFLAGS) $(MOVE_TEST) -o stopwatch-move
loop-test: $(LOOP_TEST)
	$(CXX) $(CXXFLAGS) $(LOOP_TEST) -o loop-test
read-test: $(READ_TEST)
	$(CXX) $(CXXFLAGS) $(READ_TEST) -o read-test

clean:
	rm -f stopwatch-test stopwatch-string stopwatch-move loop-test read-test
