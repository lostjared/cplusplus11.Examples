CXX=c++
BOOST_DIR=/opt/local/boost
FLAGS= -std=c++11   -I$(BOOST_DIR)/include 
FILES=filesend.o main.o
LDFLAGS= -L$(BOOST_DIR)/lib -lboost_system

all:
	$(CXX) $(FLAGS) filesend.cpp -c -o filesend.o
	$(CXX) $(FLAGS) main.cpp -c -o main.o
	$(CXX) $(FLAGS) $(FILES) -o getfile  $(LDFLAGS)
	$(CXX) $(FLAGS) server.cpp filesend.cpp  -o servtest $(LDFLAGS)
clean:
	rm -f getfile servtest  *.o
