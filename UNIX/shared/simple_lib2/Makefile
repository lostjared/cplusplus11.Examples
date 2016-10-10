CXX_FLAGS=-std=c++11

all: libdemo.dylib program

libdemo.dylib: lib.cpp
	$(CXX) $(CXX_FLAGS) -fPIC lib.cpp -shared -dynamiclib -install_name "libdemo.dylib.1" -o libdemo.dylib.1.0.0
	ln -sf libdemo.dylib.1.0.0 libdemo.dylib.1
	ln -sf libdemo.dylib.1 libdemo.dylib

program: prog.cpp header.h
	$(CXX) $(CXX_FLAGS) prog.cpp -o program -L. -ldemo
clean:
	rm -f program libdemo.dylib libdemo.dylib.1 libdemo.dylib.1.0.0
