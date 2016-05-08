SOURCES=main.cpp
SDL_PATH=/opt/local
CXXFLAGS= -std=c++11 -O2 `$(SDL_PATH)/bin/sdl-config --cflags`
LDFLAGS=-L$(SDL_PATH)/lib $(SDL_PATH)/lib/libX*.a  $(SDL_PATH)/lib/libSDL.a $(SDL_PATH)/lib/libSDLmain.a $(SDL_PATH)/lib/libxcb.a -Wl,-framework,OpenGL -Wl,-framework,Cocoa -Wl,-framework,ApplicationServices -Wl,-framework,Carbon -Wl,-framework,AudioToolbox -Wl,-framework,AudioUnit -Wl,-framework,IOKit

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<
joy-test: main.o
	$(CXX) $(LDFLAGS) main.o -o joy-test
clean:
	rm -f joy-test *.o
