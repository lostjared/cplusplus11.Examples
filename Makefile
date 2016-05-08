CXX=c++
CXXFLAGS=-Wall -std=c++11

SUBDIR=e algorithm allocator array arraybyte assert auto bin_to_array bitset calculator cast cgi chrono compile_test compress_code constexpr databyte db download enum finally friend fstream function_objects function_syntax generic hash hero init iterator join  lambda lexer list_to_array m3ugen main  member misc move mutable namespace operator override persist pool random rar_extract readfast_textscroll regex rename_files replace rvalue set shared smart_pointer sort sort_files static stream_insert_iterators stringstream symbol_table test thread tilemap transfer trim_lines try tuple typeid unordered_map variadic vector

all:
	for dir in $(SUBDIR); do \
	make -C $$dir; \
	done
