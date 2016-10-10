CXX_FLAGS= -std=c++11

all: insert_iterator_test stream_iterator_test
insert_iterator_test: insert_iterator.cpp
	$(CXX) $(CXX_FLAGS) insert_iterator.cpp -o insert_iterator_test
stream_iterator_test: stream_iterator.cpp
	$(CXX) $(CXX_FLAGS) stream_iterator.cpp -o stream_iterator_test
clean:
	rm -f insert_iterator_test stream_Iterator_test

