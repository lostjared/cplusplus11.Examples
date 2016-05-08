CXX=c++
CXX_FLAGS=-std=c++11


SOURCE_FILES= mxl-test.cpp program1-test.cpp main.cpp program-test2.cpp
SOURCE_OBJECTS=main.o mxl-test.o program-test1.o program-test2.o


%.o: %.cpp mxl.hpp lexer.hpp
	$(CXX) $(CXX_FLAGS)  -c -o $@ $<  

code: $(SOURCE_OBJECTS)
	$(CXX) $(CXX_FLAGS) main.o -o lexer-test 
	$(CXX) $(CXX_FLAGS) mxl-test.o -o mxl-test
	$(CXX) $(CXX_FLAGS) program-test1.o -o program-test1
	$(CXX) $(CXX_FLAGS) program-test2.o -o program-test2
clean:
	rm -f lexer-test mxl-test program-test1 *.o
install: 
	cp lexer-test /usr/local/bin
