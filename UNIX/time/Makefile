CXX_FLAGS= -std=c++11

all: gettime-test tick-test

gettime-test: gettime.cpp
	$(CXX) $(CXX_FLAGS) gettime.cpp -o gettime-test

tick-test: gettickcount.cpp
	$(CXX) $(CXX_FLAGS) gettickcount.cpp -o tick-test

clean:
	rm -f gettime-test tick-test

