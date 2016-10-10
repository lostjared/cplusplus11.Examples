CFLAGS=-Wall -std=c++11  

all: try-test try-test2

try-test: try.cc
	$(CXX) try.cc -o try-test $(CFLAGS)
try-test2: try2.cc
	$(CXX) try2.cc -o try-test2 $(CFLAGS)
clean:
	rm -rf try-test try-test2
