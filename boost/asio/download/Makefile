CXX=c++
BOOST_DIR=/opt/local/boost
FLAGS= -std=c++11   -I$(BOOST_DIR)/include 
FILES=filesend.o main.o
LDFLAGS= -L$(BOOST_DIR)/lib -lboost_system

all:
	$(CXX) $(FLAGS) download.cpp  -o download-test  $(LDFLAGS)
clean:
	rm -f download-test
