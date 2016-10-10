CFLAGS= -std=c++11

all: textscroll plaintext_scroll linescroll

textscroll: scroll.cpp
	$(CXX) $(CFLAGS) scroll.cpp -o textscroll
plaintext_scroll: textscroll.cpp
	$(CXX) $(CFLAGS) textscroll.cpp -o plaintext_scroll
linescroll: linescroll.cpp
	$(CXX) $(CFLAGS) linescroll.cpp -o linescroll
clean:
	rm -f textscroll plaintext_scroll linescroll
