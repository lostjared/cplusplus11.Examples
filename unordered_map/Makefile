FLAGS=-Wall -std=c++11  
all: unordered-test test2

unordered-test: unordered_map_test.cc
	$(CXX) unordered_map_test.cc -o unordered-test $(FLAGS)
test2: print_recursive.cc
	$(CXX) print_recursive.cc -o test2 $(FLAGS)
clean:
	rm -rf unordered-test test2
