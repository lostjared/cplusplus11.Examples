CXXFLAGS=-std=c++11
SOURCE=tokenize.cpp
COLLECT_SOURCE=collect_tokens.cpp
OUTPUT=tokenize-test
COLLECT_OUTPUT=collect-test
PARSE_SOURCE=parse.cpp
PARSE_OUTPUT=parse-test
all:
	$(CXX) $(CXXFLAGS) $(SOURCE) -o $(OUTPUT)
	$(CXX) $(CXXFLAGS) $(COLLECT_SOURCE) -o $(COLLECT_OUTPUT)
	$(CXX) $(CXXFLAGS) $(PARSE_SOURCE) -o $(PARSE_OUTPUT)
clean:
	rm -f $(OUTPUT) $(COLLECT_OUTPUT) $(PARSE_OUTPUT)
