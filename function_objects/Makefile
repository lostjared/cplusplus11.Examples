CXX_FLAGS= -std=c++11

all: func1-test func2-test

func1-test: func1.cpp
	$(CXX) $(CXX_FLAGS) func1.cpp -o func1-test -pthread
func2-test: func2.cpp
	$(CXX) $(CXX_FLAGS) func2.cpp -o func2-test -pthread
clean:
	rm -f func1-test func2-test

