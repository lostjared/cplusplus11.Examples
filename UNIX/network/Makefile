CXX_FLAGS=-std=c++11 -Wall

all: af_unix-stream-server af_unix-stream-client


af_unix-stream-server: af_unix-stream-server.cpp
	$(CXX) $(CXX_FLAGS) af_unix-stream-server.cpp -o af_unix-stream-server

af_unix-stream-client: af_unix-stream-client.cpp
	$(CXX) $(CXX_FLAGS) af_unix-stream-client.cpp -o af_unix-stream-client

clean:
	rm -f af_unix-stream-client af_unix-stream-server

	
	
