CXX_FLAGS=-std=c++11
CV_CFLAGS=`pkg-config opencv --cflags`
CV_LDFLAGS=`pkg-config opencv --libs`
PROGRAM=example01

$(PROGRAM): $(PROGRAM).cpp
	$(CXX) $(CXX_FLAGS) $(CV_CFLAGS) $(PROGRAM).cpp -o $(PROGRAM) $(CV_LDFLAGS)
clean:
	rm -f $(PROGRAM)

