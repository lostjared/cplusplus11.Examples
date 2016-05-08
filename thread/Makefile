CXX=c++
FLAGS=-Wall -std=c++11 
all:
	$(CXX) $(FLAGS)  thread_test.cc -o thread-test1 
	$(CXX) $(FLAGS)  async_test.cc -o async-test
	$(CXX) $(FLAGS)  async_test2.cc -o async-test2
	$(CXX) $(FLAGS)  async_test3.cc -o async-test3
	$(CXX) $(FLAGS)  promise.cc -o promise-test
	$(CXX) $(FLAGS) async_test4.cpp -o async-test4 
	$(CXX) $(FLAGS) detach.cpp -o detach-test
	$(CXX) $(FLAGS) atomic.cpp -o atomic-test
clean:
	rm -f thread-test1 async-test async-test2 async-test3 async-test4  promise-test detach-test atomic-test
