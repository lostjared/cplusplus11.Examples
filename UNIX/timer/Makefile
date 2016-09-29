CXX_FLAGS=-std=c++11

all: timer-test alarm-test nano-test nano-sleep-test

timer-test: timer.cpp
	$(CXX) $(CXX_FLAGS) timer.cpp -o timer-test

alarm-test: alarm.cpp
	$(CXX) $(CXX_FLAGS) alarm.cpp -o alarm-test

nano-test: nanosleep.cpp
	$(CXX) $(CXX_FLAGS) nanosleep.cpp -o nano-test

nano-sleep-test: nanosleep_wait.cpp
	$(CXX) $(CXX_FLAGS) nanosleep_wait.cpp -o nano-sleep-test

clean:
	rm -f alarm-test timer-test nano-test nano-sleep-test
