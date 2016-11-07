CXX_FLAGS=-std=c++11

all: bin2cpp memfile-demo extract-image

memfile-demo: memfile_demo.cpp
	$(CXX) $(CXX_FLAGS) -I. memfile_demo.cpp resource/resource.cpp -o memfile-demo

bin2cpp: bin2cpp.cpp
	$(CXX) $(CXX_FLAGS) bin2cpp.cpp -o bin2cpp

extract-image: extract_image.cpp
	$(CXX) $(CXX_FLAGS) extract_image.cpp image_res/floyd.cpp  -o extract-image -I.

install: bin2cpp
	cp bin2cpp /usr/local/bin

clean:
	rm -f bin2cpp memfile-demo extract-image
