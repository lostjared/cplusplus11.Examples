SOURCE_FILE=forktest.cpp
OUTPUT_FILE=fork-test

CFLAGS=-std=c++11 

all: $(OUTPUT_FILE) test-fork

$(OUTPUT_FILE): $(SOURCE_FILE)
	$(CXX) $(CFLAGS) $(SOURCE_FILE) -o $(OUTPUT_FILE)

test-fork: fork.cpp
	$(CXX) $(CFLAGS) fork.cpp -o test-fork

clean:
	rm -f $(OUTPUT_FILE) test-fork

