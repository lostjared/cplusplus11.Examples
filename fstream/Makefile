FLAGS= -std=c++11  -O2

all: readwrite-test text-test

readwrite-test: readwrite.cc
	$(CXX) $(FLAGS) readwrite.cc -o readwrite-test
text-test: textoutput.cc
	$(CXX) $(FLAGS) textoutput.cc -o text-test
clean:
	rm -f readwrite-test text-test
