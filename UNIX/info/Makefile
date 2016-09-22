CXX_FLAGS=-std=c++11

all: uname-info stat-info

uname-info: uname.cpp
	$(CXX) $(CXX_FLAGS) uname.cpp -o uname-info

stat-info: stat.cpp
	$(CXX) $(CXX_FLAGS) stat.cpp -o stat-info

clean:
	rm -f uname-info stat-info
