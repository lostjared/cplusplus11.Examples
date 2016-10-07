CXX=c++
CXXFLAGS= -I/usr/include -std=c++11  -Wall `sdl2-config --cflags`
LDFLAGS= `sdl2-config --static-libs`  /usr/lib/libGLEW.a

all: gltest

gltest:
	$(CXX) gltest.cpp -o gltest $(CXXFLAGS) $(LDFLAGS)
clean:
	rm -f gltest
