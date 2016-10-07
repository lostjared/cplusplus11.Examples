### be sure to set SDL_PATH to the path of SDL2

CXX=c++
SDL_PATH=
CPP_FLAGS= -std=c++11 -stdlib=libc++ -Wall
CXX_FLAGS= `sdl2-config --cflags`
LD_FLAGS= `freetype-config --libs` `sdl2-config --static-libs` -lSDL2_ttf

all: 3card-prog

3card-prog: 3card.cpp
	$(CXX) $(CPP_FLAGS) 3card.cpp -c -o 3card.o $(CXX_FLAGS)
	$(CXX) $(CPP_FLAGS) 3card.o -o 3card-prog $(LD_FLAGS)
clean:
	rm -f 3card-prog *.o
