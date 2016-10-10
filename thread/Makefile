FLAGS=-Wall -std=c++11 
all: thread-test1 async-test async-test2 async-test3 promise-test async-test4 detach-test atomic-test

thread-test1: thread_test.cc
	$(CXX) $(FLAGS)  thread_test.cc -o thread-test -pthread
async-test: async_test.cc 
	$(CXX) $(FLAGS)  async_test.cc -o async-test -pthread
async-test2: async_test2.cc
	$(CXX) $(FLAGS)  async_test2.cc -o async-test2 -pthread
async-test3: async_test3.cc
	$(CXX) $(FLAGS)  async_test3.cc -o async-test3 -pthread
promise-test: promise.cc
	$(CXX) $(FLAGS)  promise.cc -o promise-test -pthread
async-test4: async_test4.cpp
	$(CXX) $(FLAGS) async_test4.cpp -o async-test4 -pthread
detach-test: detach.cpp 
	$(CXX) $(FLAGS) detach.cpp -o detach-test -pthread
atomic-test: atomic.cpp
	$(CXX) $(FLAGS) atomic.cpp -o atomic-test -pthread
clean:
	rm -f thread-test1 async-test async-test2 async-test3 async-test4  promise-test detach-test atomic-test
