CXX_FLAGS= -std=c++11 -O2

all: compress-code format-code

compress-code: main.cpp
	$(CXX) $(CXX_FLAGS) main.cpp -o compress-code
format-code: format.cpp 
	$(CXX) $(CXX_FLAGS) format.cpp -o format-code
clean:
	rm -f compress-code format-code
