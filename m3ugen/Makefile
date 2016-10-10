
CFLAGS= -Wall -O3


all: m3ugen

m3ugen: main.cc m3u.hpp
	$(CXX) $(CFLAGS) main.cc -o m3ugen 
install: all
	cp m3ugen /usr/local/bin
clean:
	rm -f m3ugen
