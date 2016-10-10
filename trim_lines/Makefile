CXX=c++
CXX_FLAGS=-std=c++11
OBJECT_SOURCE=triml

all: $(OBJECT_SOURCE)

$(OBJECT_SOURCE): $(OBJECT_SOURCE).cpp
	$(CXX) $(CXX_FLAGS) $(OBJECT_SOURCE).cpp -o $(OBJECT_SOURCE)
clean:
	rm -f $(OBJECT_SOURCE)
install:
	cp $(OBJECT_SOURCE) /usr/local/bin



