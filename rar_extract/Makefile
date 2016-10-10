CXX_FLAGS= -std=c++11 -O2
SOURCE_FILES=unrar_extract.cpp
all: unrar_extract

unrar_extract: $(SOURCE_FILES)
	$(CXX) $(CXX_FLAGS) $(SOURCE_FILES)  -o unrar_extract
clean:
	rm -f unrar_extract
install: 
	cp unrar_extract /usr/bin/unrar_extract
