
CFLAGS=  -I.-O2 -std=c++11
LDFLAGS=
CPP_FILES := $(wildcard *.cpp)
OBJ_FILES := $(addprefix ,$(notdir $(CPP_FILES:.cpp=.o)))

%.o: %.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<
  
all: $(OBJ_FILES) 
	$(CXX) $(OBJ_FILES)  -o ats-dbg  $(LDFLAGS)

clean:
	rm -f ats-dbg *.o 
