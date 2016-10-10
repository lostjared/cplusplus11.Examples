CXX_FLAGS=-std=c++11

all: libdemo.dylib program

libdemo.dylib: lib.cpp
	$(CXX) $(CXX_FLAGS) -fPIC lib.cpp -shared -o libdemo.dylib

program: prog.cpp header.h
	$(CXX) $(CXX_FLAGS) prog.cpp -o program -ldl
clean:
	rm -f program libdemo.dylib
