CXX=c++
CFLAGS= -Wall -O3

all:
	$(CXX) $(CFLAGS) main.cc -o m3ugen 
install: all
	cp m3ugen /opt/local/bin
clean:
	rm -f m3ugen
