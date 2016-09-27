CXX_FLAGS=-std=c++11

all: signal-test-send signal-test-recv sigaction-test isprocess-test

signal-test-send: signal-test-send.cpp
	$(CXX) $(CXX_FLAGS) signal-test-send.cpp -o signal-test-send

signal-test-recv: signal-test.cpp
	$(CXX) $(CXX_FLAGS) signal-test.cpp -o signal-test-recv

sigaction-test: sigaction-test.cpp
	$(CXX) $(CXX_FLAGS) sigaction-test.cpp -o sigaction-test

isprocess-test: isprocess.cpp
	$(CXX) $(CXX_FLAGS) isprocess.cpp -o isprocess-test

clean:
	rm -f signal-test-send signal-test-recv sigaction-test isprocess-test
