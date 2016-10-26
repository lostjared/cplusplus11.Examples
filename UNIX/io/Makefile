CXX_FLAGS=-std=c++11 -Wall

all: read-test rdwr-test redir-test poll-test signal-io
	
rdwr-test: io-readwrite.cpp
	$(CXX) $(CXX_FLAGS) io-readwrite.cpp -o rdwr-test

read-test: io-read.cpp
	$(CXX) $(CXX_FLAGS) io-read.cpp -o read-test

redir-test: io-redirect.cpp
	$(CXX) $(CXX_FLAGS) io-redirect.cpp -o redir-test

poll-test: poll.cpp
	$(CXX) $(CXX_FLAGS) poll.cpp -o poll-test

signal-io: signal-io.cpp
	$(CXX) $(CXX_FLAGS) signal-io.cpp -o signal-io-test


clean:
	rm -f read-test rdwr-test redir-test poll-test signal-io-test

