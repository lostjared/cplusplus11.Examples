FLAGS= -Wall -std=c++11  

all: test1-test st-test type-test temp-test temp-test2 temp-test-2

test1-test: test.cc
	$(CXX) test.cc -o test1-test $(FLAGS)
st-test: static_assert_test.cc
	$(CXX) static_assert_test.cc -o st-test $(FLAGS)
type-test: typearr.cc
	$(CXX) typearr.cc -o type-test $(FLAGS)
temp-test: temp_test.cc
	$(CXX) temp_test.cc -o temp-test $(FLAGS)
temp-test2: temp_test2.cc
	$(CXX) temp_test2.cc -o temp-test2 $(FLAGS)
temp-test-2: test2.cc
	$(CXX) test2.cc -o temp-test-2 $(FLAGS)
clean:
	rm -f test1-test st-test type-test temp-test temp-test2 temp-test-2

