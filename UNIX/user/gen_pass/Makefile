#CXX=clang++-5.0
CXXFLAGS=-std=c++11
LDFLAGS= 
GEN_PASS=gen_pass

all: $(GEN_PASS)

$(GEN_PASS): $(GEN_PASS).cpp
	$(CXX) $(CXXFLAGS) $(GEN_PASS).cpp -o $(GEN_PASS) $(LDFLAGS)
clean:
	rm -f $(GEN_PASS)

