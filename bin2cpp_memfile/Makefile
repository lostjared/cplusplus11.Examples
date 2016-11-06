CXX_FLAGS=-std=c++11

all: bin2cpp memfile-demo

memfile-demo: memfile_demo.cpp
	$(CXX) $(CXX_FLAGS) memfile_demo.cpp memfile.hpp.cpp -o memfile-demo

bin2cpp: bin2cpp.cpp
	$(CXX) $(CXX_FLAGS) bin2cpp.cpp -o bin2cpp

install: bin2cpp
	cp bin2cpp /usr/local/bin

clean:
	rm -f bin2cpp memfile-demo
