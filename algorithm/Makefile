CXX_FLAGS= -std=c++11

all: for_each_test transform_test find_if_test sort-test

for_each_test: for_each.cpp
	$(CXX) $(CXX_FLAGS) for_each.cpp -o for_each_test
transform_test: transform.cpp
	$(CXX) $(CXX_FLAGS) transform.cpp -o transform_test
find_if_test: find_if.cpp
	$(CXX) $(CXX_FLAGS) find_if.cpp -o find_if_test
sort-test: sort.cpp
	$(CXX) $(CXX_FLAGS) sort.cpp -o sort-test
clean:
	rm -f for_each_test transform_test find_if_test sort-test
