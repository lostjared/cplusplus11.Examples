CXX=c++
BOOST_DIR=/opt/local/boost
FLAGS= -std=c++11   -I$(BOOST_DIR)/include 
FILES=server.o
LDFLAGS= -L$(BOOST_DIR)/lib -lboost_system

all:
	$(CXX) $(FLAGS) server.cpp -c -o server.o
	$(CXX) $(FLAGS) $(FILES) -o asynctest-server  $(LDFLAGS)
	$(CXX) $(FLAGS) client.cpp  -o asynctest-client  $(LDFLAGS)
clean:
	rm -f asynctest-client asynctest-server  *.o
