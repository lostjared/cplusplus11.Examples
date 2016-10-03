PTHREAD_TEST_SOURCE=pthread-test.cpp
PTHREAD_TEST_OUTPUT=pthread-test
CFLAGS=-std=c++11

all: $(PTHREAD_TEST_OUTPUT) pthread-self-test pthread-mutex-test pthread-cond-test pthread-once-test pthread-cancel-test

$(PTHREAD_TEST_OUTPUT): $(PTHREAD_TEST_SOURCE)
	$(CXX) $(CFLAGS) $(PTHREAD_TEST_SOURCE) -o $(PTHREAD_TEST_OUTPUT) -pthread

pthread-self-test: pthread-self.cpp
	$(CXX) $(CFLAGS) pthread-self.cpp -o pthread-self-test -pthread

pthread-mutex-test: pthread-mutex.cpp
	$(CXX) $(CFLAGS) pthread-mutex.cpp -o pthread-mutex-test -pthread
pthread-cond-test: pthread-cond.cpp
	$(CXX) $(CFLAGS) pthread-cond.cpp -o pthread-cond-test -pthread
pthread-once-test: pthread-once.cpp
	$(CXX) $(CFLAGS) pthread-once.cpp -o pthread-once-test -pthread
pthread-cancel-test: pthread-cancel.cpp
	$(CXX) $(CFLAGS) pthread-cancel.cpp -o pthread-cancel-test -pthread

clean:
	rm -f $(PTHREAD_TEST_OUTPUT) pthread-self-test pthread-mutex-test pthread-cond-test pthread-once-test pthread-cancel-test
