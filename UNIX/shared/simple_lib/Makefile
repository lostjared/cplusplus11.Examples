CXX_FLAGS=-std=c++11

all: libdemo.dylib prog

libdemo.dylib: lib.cpp
	$(CXX) $(CXX_FLAGS) -fPIC lib.cpp -shared -o libdemo.dylib

prog: prog.cpp header.h
	$(CXX) $(CXX_FLAGS) prog.cpp -o program -L. -ldemo
clean:
	rm -f program libdemo.dylib
