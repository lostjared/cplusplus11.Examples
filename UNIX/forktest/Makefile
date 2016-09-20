SOURCE_FILE=forktest.cpp
OUTPUT_FILE=fork-test

CFLAGS=-std=c++11 

all: $(OUTPUT_FILE)

$(OUTPUT_FILE): $(SOURCE_FILE)
	$(CXX) $(CFLAGS) $(SOURCE_FILE) -o $(OUTPUT_FILE)
clean:
	rm -f $(OUTPUT_FILE)

