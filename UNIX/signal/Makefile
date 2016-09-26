CXX_FLAGS=-std=c++11

all: signal-test-send signal-test-recv

signal-test-send: signal-test-send.cpp
	$(CXX) $(CXX_FLAGS) signal-test-send.cpp -o signal-test-send

signal-test-recv: signal-test.cpp
	$(CXX) $(CXX_FLAGS) signal-test.cpp -o signal-test-recv

clean:
	rm -f signal-test-send signal-test-recv
