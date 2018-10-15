CFLAGS= -std=c++11 -O3 `pkg-config glew sdl2 acidcam opencv --cflags`
LDADD = `pkg-config glew sdl2 opencv acidcam --libs` -framework OpenGL

CPP_FILES := $(wildcard *.cpp)
OBJ_FILES := $(addprefix ,$(notdir $(CPP_FILES:.cpp=.o)))

%.o: %.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<
  
all: $(OBJ_FILES) 
	$(CXX) $(OBJ_FILES)  -o acid_cube  $(LDADD)

clean:
	rm -f *.o ./acid_cube

install:
	cp acid_cube /usr/local/bin
