CXX=clang++
SDL_CONFIG_PATH=/opt/local/bin
FLAGS= -std=c++11   `$(SDL_CONFIG_PATH)/sdl-config --cflags --static-libs` 

all:
	$(CXX) test.cpp -o sdl-test $(FLAGS)
clean:
	rm -f sdl-test
