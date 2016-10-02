PTHREAD_TEST_SOURCE=pthread-test.cpp
PTHREAD_TEST_OUTPUT=pthread-test
CFLAGS=-std=c++11

all: $(PTHREAD_TEST_OUTPUT) pthread-self-test

$(PTHREAD_TEST_OUTPUT): $(PTHREAD_TEST_SOURCE)
	$(CXX) $(CFLAGS) $(PTHREAD_TEST_SOURCE) -o $(PTHREAD_TEST_OUTPUT) -pthread

pthread-self-test: pthread-self.cpp
	$(CXX) $(CFLAGS) pthread-self.cpp -o pthread-self-test -pthread
clean:
	rm -f $(PTHREAD_TEST_OUTPUT) pthread-self-test
