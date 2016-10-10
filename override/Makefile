CXX=c++
FLAGS= -Wall -std=c++11  

all: override-test virtual-test

override-test: override_test.cc
	$(CXX) override_test.cc -o override-test $(FLAGS)
virtual-test: virtual_base.cc
	$(CXX) virtual_base.cc -o virtual-test $(FLAGS)
clean:
	rm -f override-test virtual-test
