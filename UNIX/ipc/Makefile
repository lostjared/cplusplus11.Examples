CXX_FLAGS=-std=c++11

all: popen-test pipe-test


popen-test: popen.cpp
	$(CXX) $(CXX_FLAGS) popen.cpp -o popen-test

pipe-test: pipe.cpp
	$(CXX) $(CXX_FLAGS) pipe.cpp -o pipe-test

clean:
	rm -f popen-test pipe-test
