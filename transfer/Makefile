
CXX_FLAGS= -Wall -O3 -std=c++11  

all: transfer-tool

transfer-tool: transfer.cc
	$(CXX) transfer.cc -o transfer-tool  $(CXX_FLAGS) -pthread

clean:
	rm -f transfer-tool

