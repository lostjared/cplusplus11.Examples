CXX_FLAGS=-std=c++11

all: dir-test dir-find


dir-test: dir-test.cpp
	$(CXX) $(CXX_FLAGS) dir-test.cpp -o dir-test

dir-find: dir-find.cpp
	$(CXX) $(CXX_FLAGS) dir-find.cpp -o dir-find

clean:
	rm -f dir-test dir-find
