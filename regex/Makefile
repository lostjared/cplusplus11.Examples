FLAGS=-Wall -std=c++11  

all: regex-test regex-test2

regex-test: regex_test.cc
	$(CXX) regex_test.cc -o regex-test $(FLAGS)
regex-test2: regex.cpp
	$(CXX) $(FLAGS)  regex.cpp -o regex-test2 

clean:
	rm -rf regex-test regex-test2

