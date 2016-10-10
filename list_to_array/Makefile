
CXX_FLAGS= -std=c++11
OUTPUT_FILE=list_to_array

all: $(OUTPUT_FILE)

$(OUTPUT_FILE): $(OUTPUT_FILE).cpp
	$(CXX) $(CXX_FLAGS) $(OUTPUT_FILE).cpp -o $(OUTPUT_FILE) 
clean:
	rm -f $(OUTPUT_FILE)
install:
	cp $(OUTPUT_FILE) /usr/local/bin
