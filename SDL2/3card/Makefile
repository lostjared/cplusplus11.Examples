### be sure to set SDL_PATH to the path of SDL2

CXX=c++
SDL_PATH=/opt/local/sdl
CPP_FLAGS= -std=c++11 -stdlib=libc++ -Wall
CXX_FLAGS= `$(SDL_PATH)/bin/sdl2-config --cflags`
LD_FLAGS= `$(SDL_PATH)/bin/freetype-config --libs` `$(SDL_PATH)/bin/sdl2-config --static-libs` $(SDL_PATH)/lib/libSDL2_ttf.a

all:
	$(CXX) $(CPP_FLAGS) 3card.cpp -c -o 3card.o $(CXX_FLAGS)
	$(CXX) $(CPP_FLAGS) 3card.o -o 3card-prog $(LD_FLAGS)
clean:
	rm -f 3card-prog *.o
