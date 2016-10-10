CXX=c++
FLAGS=-Wall -std=c++11 
all: constexpr-test constexpr-test2 constexpr-test3
constexpr-test: constexpr.cc
	$(CXX)  $(FLAGS)  constexpr.cc -o constexpr-test  
constexpr-test2: constexpr-test.cc
	$(CXX)  $(FLAGS)  constexpr-test.cc -o constexpr-test2
constexpr-test3: constexpr_example.cpp
	$(CXX) $(FLAGS) constexpr_example.cpp -o constexpr-test3
clean:
	rm -f constexpr-test constexpr-test2 constexpr-test3
