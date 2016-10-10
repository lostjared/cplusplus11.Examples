
CXX_FLAGS=-std=c++11


SOURCE_FILES= mxl-test.cpp program1-test.cpp main.cpp program-test2.cpp
SOURCE_OBJECTS=main.o mxl-test.o program-test1.o program-test2.o

all: lexer-test mxl-test program-test1 program-test2

lexer-test: main.cpp
	$(CXX) $(CXX_FLAGS) main.cpp -o lexer-test
mxl-test: mxl-test.cpp 
	$(CXX) $(CXX_FLAGS) mxl-test.cpp -o mxl-test
program-test1: program-test1.cpp
	$(CXX) $(CXX_FLAGS) program-test1.cpp -o program-test1
program-test2: program-test2.cpp
	$(CXX) $(CXX_FLAGS) program-test2.cpp -o program-test2
clean:
	rm -f lexer-test mxl-test program-test1 program-test2
install: 
	cp lexer-test /usr/local/bin
