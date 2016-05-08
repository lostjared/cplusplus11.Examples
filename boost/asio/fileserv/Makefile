CXX=c++
BOOST_DIR=/opt/local/boost
FLAGS= -std=c++11   -I$(BOOST_DIR)/include 
FILES=file-server.o
LDFLAGS= -L$(BOOST_DIR)/lib -lboost_system

all:
	$(CXX) $(FLAGS) file-server.cpp -c -o file-server.o
	$(CXX) $(FLAGS) $(FILES) -o fileserv $(LDFLAGS)
clean:
	rm -f *.o fileserv
