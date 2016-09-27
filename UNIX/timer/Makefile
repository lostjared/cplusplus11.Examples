CXX_FLAGS=-std=c++11

all: timer-test alarm-test

timer-test: timer.cpp
	$(CXX) $(CXX_FLAGS) timer.cpp -o timer-test
alarm-test: alarm.cpp
	$(CXX) $(CXX_FLAGS) alarm.cpp -o alarm-test

clean:
	rm -f alarm-test timer-test
