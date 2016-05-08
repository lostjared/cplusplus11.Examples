CXX=c++
FLAGS= -Wall -std=c++11  

all:
	$(CXX) test.cc -o test1-test $(FLAGS)
	$(CXX) static_assert_test.cc -o st-test $(FLAGS)
	$(CXX) typearr.cc -o type-test $(FLAGS)
	$(CXX) temp_test.cc -o temp-test $(FLAGS)
	$(CXX) temp_test2.cc -o temp-test2 $(FLAGS)
	$(CXX) test2.cc -o temp-test-2 $(FLAGS)
clean:
	rm -f test1-test st-test type-test temp-test temp-test2 temp-test-2

