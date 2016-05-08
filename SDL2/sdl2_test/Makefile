CXX=c++
SDL_PATH=/opt/local/sdl

FLAGS=-std=c++11  `sdl2-config --cflags --libs`  -framework OpenGL
all:
	$(CXX) SDL2_test.cpp -o sdl2-test $(FLAGS) 
	$(CXX) SDL2_test2.cpp -o sdl2-test2 $(FLAGS)
	$(CXX) pong.cpp -o pong-test $(FLAGS)
clean:
	rm -f sdl2-test sdl2-test2 pong-test
