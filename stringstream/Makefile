CFLAGS=-std=c++11   -O2 -Wall

all: ss-test iss-test iss2-test

ss-test: ss.cc
	$(CXX) ss.cc -o ss-test $(FLAGS)
iss-test: iss.cc 
	$(CXX) iss.cc -o iss-test $(FLAGS)
iss2-test: iss2.cc
	$(CXX) iss2.cc -o iss2-test $(FLAGS)
clean:
	rm -f ss-test iss-test iss2-test
