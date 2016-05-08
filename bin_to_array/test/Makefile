CXX=c++
BIN2CPP=bin2cpp
CXX_FLAGS=-std=c++11
SOURCE=test.cpp

all:
	$(BIN2CPP) $(SOURCE)
	$(CXX) $(CXX_FLAGS) $(SOURCE) -c -o test.o
	$(CXX) $(CXX_FLAGS) $(SOURCE).cpp -c -o test_cpp.o
	$(CXX) $(CXX_FLAGS) test.o test_cpp.o -o test-program
clean:
	rm -f *.o test-program
