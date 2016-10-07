CXXFLAGS=-O2

all: cpp_tokenize

cpp_tokenize: sourcefile.cpp
	$(CXX)  $(CXXFLAGS) sourcefile.cpp -o cpp_tokenize
	chmod 755 cpp_tokenize
clean:
	rm -f cpp_tokenize
