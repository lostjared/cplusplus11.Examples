CXX_FLAGS=-std=c++11 -Wall

all: af_unix-stream-server af_unix-stream-client unix-udp-srv unix-udp-cli socktest-test


af_unix-stream-server: af_unix-stream-server.cpp
	$(CXX) $(CXX_FLAGS) af_unix-stream-server.cpp -o af_unix-stream-server

af_unix-stream-client: af_unix-stream-client.cpp
	$(CXX) $(CXX_FLAGS) af_unix-stream-client.cpp -o af_unix-stream-client

unix-udp-srv: unix-udp-srv.cpp
	$(CXX) $(CXX_FLAGS) unix-udp-srv.cpp -o unix-udp-srv

unix-udp-cli: unix-udp-cli.cpp
	$(CXX) $(CXX_FLAGS) unix-udp-cli.cpp -o unix-udp-cli
socktest-test: socktest.cpp socket.cpp
	$(CXX) $(CXX_FLAGS) socktest.cpp socket.cpp -o socktest-test

clean:
	rm -f af_unix-stream-client af_unix-stream-server unix-udp-srv unix-udp-cli socktest-test

	
	
