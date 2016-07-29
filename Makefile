CFLAGS= -std=c++11
all: 
	mkdir -p build
	$(CXX) $(CFLAGS) ./algorithm/find_if.cpp -o build/find_if
	$(CXX) $(CFLAGS) ./algorithm/for_each.cpp -o build/for_each
	$(CXX) $(CFLAGS) ./algorithm/sort.cpp -o build/sort
#	$(CXX) $(CFLAGS) ./algorithm/transform.cpp -o build/transform
	$(CXX) $(CFLAGS) ./arraybyte/main.cpp -o build/main
	$(CXX) $(CFLAGS) ./assert/main.cpp -o build/main
	$(CXX) $(CFLAGS) ./auto/autotest2.cpp -o build/autotest2
	$(CXX) $(CFLAGS) ./bin_to_array/bin2cpp.cpp -o build/bin2cpp
#	$(CXX) $(CFLAGS) ./bin_to_array/bin2cpp.cpp.cpp -o build/bin2cpp.cpp
#	$(CXX) $(CFLAGS) ./bin_to_array/bin2cpp.cpp.h -o build/bin2cpp.cpp
#	$(CXX) $(CFLAGS) ./bin_to_array/test/test.cpp -o build/test
#	$(CXX) $(CFLAGS) ./bin_to_array/test/test.cpp.cpp -o build/test.cpp
#	$(CXX) $(CFLAGS) ./bin_to_array/test/test.cpp.h -o build/test.cpp
#	$(CXX) $(CFLAGS) ./boost/asio/async_server/client.cpp -o build/client
#	$(CXX) $(CFLAGS) ./boost/asio/async_server/server.cpp -o build/server
#	$(CXX) $(CFLAGS) ./boost/asio/download/download.cpp -o build/download
#	$(CXX) $(CFLAGS) ./boost/asio/ex1/filesend.cpp -o build/filesend
#	$(CXX) $(CFLAGS) ./boost/asio/ex1/main.cpp -o build/main
#	$(CXX) $(CFLAGS) ./boost/asio/ex1/server.cpp -o build/server
#	$(CXX) $(CFLAGS) ./boost/asio/filesend/filesend.cpp -o build/filesend
#	$(CXX) $(CFLAGS) ./boost/asio/filesend/main.cpp -o build/main
#	$(CXX) $(CFLAGS) ./boost/asio/filesend/server.cpp -o build/server
#	$(CXX) $(CFLAGS) ./boost/asio/fileserv/file-server.cpp -o build/file-server
#	$(CXX) $(CFLAGS) ./boost/asio/whiteboard/whiteboard.cpp -o build/whiteboard
	$(CXX) $(CFLAGS) ./calculator/main.cpp -o build/calc-main
	$(CXX) $(CFLAGS) ./cgi/sourcefile.cpp -o build/sourcefile
	$(CXX) $(CFLAGS) ./cgi/tokenize-c++/sourcefile.cpp -o build/sourcefile
	$(CXX) $(CFLAGS) ./compile_test/compile-test.cpp -o build/compile-test
	$(CXX) $(CFLAGS) ./compress_code/format.cpp -o build/format
	$(CXX) $(CFLAGS) ./compress_code/main.cpp -o build/compress-main
	$(CXX) $(CFLAGS) ./constexpr/constexpr_example.cpp -o build/constexpr_example
	$(CXX) $(CFLAGS) ./databyte/main.cpp -o build/databyte-main
	$(CXX) $(CFLAGS) ./db/db.cpp -o build/db
	$(CXX) $(CFLAGS) ./download/main.cpp -o build/download-main
	$(CXX) $(CFLAGS) ./enum/enum_class.cpp -o build/enum_class
	$(CXX) $(CFLAGS) ./function_objects/func1.cpp -o build/func1
	$(CXX) $(CFLAGS) ./function_objects/func2.cpp -o build/func2
	$(CXX) $(CFLAGS) ./hash/hash1.cpp -o build/hash1
	$(CXX) $(CFLAGS) ./hash/hash2.cpp -o build/hash2
	$(CXX) $(CFLAGS) ./hash/hash3.cpp -o build/hash3
	$(CXX) $(CFLAGS) ./init/init_test.cpp -o build/init_test
	$(CXX) $(CFLAGS) ./iterator/it.cpp -o build/it
	$(CXX) $(CFLAGS) ./iterator/it2.cpp -o build/it2
	$(CXX) $(CFLAGS) ./iterator/it3.cpp -o build/it3
	$(CXX) $(CFLAGS) ./join/main.cpp -o build/join-main
	$(CXX) $(CFLAGS) ./karma.cpp -o build/karma
	$(CXX) $(CFLAGS) ./lambda/lambda-test.cpp -o build/lambda-test
	$(CXX) $(CFLAGS) ./lexer/main.cpp -o build/lexer-main
#	$(CXX) $(CFLAGS) ./lexer/main.cpp.html -o build/main.cpp
	$(CXX) $(CFLAGS) ./lexer/mxl-test.cpp -o build/mxl-test
	$(CXX) $(CFLAGS) ./lexer/program-test1.cpp -o build/program-test1
	$(CXX) $(CFLAGS) ./lexer/program-test2.cpp -o build/program-test2
	$(CXX) $(CFLAGS) ./list_to_array/list_to_array.cpp -o build/list_to_array
	$(CXX) $(CFLAGS) ./main/main.cpp -o build/main-main
	$(CXX) $(CFLAGS) ./member_fun_pointer/main.cpp -o build/fun_main
	$(CXX) $(CFLAGS) ./misc/forward.cpp -o build/forward
	$(CXX) $(CFLAGS) ./namespace/namespace2.cpp -o build/namespace2
	$(CXX) $(CFLAGS) ./namespace/namespace3.cpp -o build/namespace3
	$(CXX) $(CFLAGS) ./operator/equal.cpp -o build/equal
	$(CXX) $(CFLAGS) ./operator_new/new.cpp -o build/new
	$(CXX) $(CFLAGS) ./override/ptr/main.cpp -o build/override-main
	$(CXX) $(CFLAGS) ./printdir/printdir.cpp -o build/printdir
	$(CXX) $(CFLAGS) ./rar_extract/unrar_extract.cpp -o build/unrar_extract
	$(CXX) $(CFLAGS) ./readfast_textscroll/linescroll.cpp -o build/linescroll
	$(CXX) $(CFLAGS) ./readfast_textscroll/scroll.cpp -o build/scroll
	$(CXX) $(CFLAGS) ./readfast_textscroll/textscroll.cpp -o build/textscroll
	$(CXX) $(CFLAGS) ./replace/main.cpp -o build/replace-main
	$(CXX) $(CFLAGS) ./rvalue/rvalue1.cpp -o build/rvalue1
	$(CXX) $(CFLAGS) ./rvalue/rvalue2.cpp -o build/rvalue2
	$(CXX) $(CFLAGS) ./rvalue/rvalue3.cpp -o build/rvalue3
	$(CXX) $(CFLAGS) ./rvalue/rvalue4.cpp -o build/rvalue4
	$(CXX) $(CFLAGS) ./rvalue/rvalue5.cpp -o build/rvalue5
#	$(CXX) $(CFLAGS) ./SDL2/3card/3card.cpp -o build/3card
#	$(CXX) $(CFLAGS) ./SDL2/opengl/cube/gltest.cpp -o build/gltest
#	$(CXX) $(CFLAGS) ./SDL2/opengl/simple/gltest.cpp -o build/gltest
#	$(CXX) $(CFLAGS) ./SDL2/sdl2_test/pong.cpp -o build/pong
#	$(CXX) $(CFLAGS) ./SDL2/sdl2_test/SDL2_test.cpp -o build/SDL2_test
#	$(CXX) $(CFLAGS) ./SDL2/sdl2_test/SDL2_test2.cpp -o build/SDL2_test2
#	$(CXX) $(CFLAGS) ./sdl2_test/pong.cpp -o build/pong
#	$(CXX) $(CFLAGS) ./sdl2_test/SDL2_test.cpp -o build/SDL2_test
#	$(CXX) $(CFLAGS) ./sdl2_test/SDL2_test2.cpp -o build/SDL2_test2
	$(CXX) $(CFLAGS) ./set/set.cpp -o build/set
	$(CXX) $(CFLAGS) ./shared/sharedtest.cpp -o build/sharedtest
	$(CXX) $(CFLAGS) ./shared/sharedtest2.cpp -o build/sharedtest2
	$(CXX) $(CFLAGS) ./smart_pointer/smart.cpp -o build/smart
	$(CXX) $(CFLAGS) ./sort/sort1.cpp -o build/sort1
	$(CXX) $(CFLAGS) ./sort/sort2.cpp -o build/sort2
	$(CXX) $(CFLAGS) ./sort_files/main.cpp -o build/sort-files-main
	$(CXX) $(CFLAGS) ./static/static1.cpp -o build/static1
	$(CXX) $(CFLAGS) ./static/static2.cpp -o build/static2
#	$(CXX) $(CFLAGS) ./stopwatch/cv-test.cpp -o build/cv-test
	$(CXX) $(CFLAGS) ./stopwatch/looptest.cpp -o build/looptest
	$(CXX) $(CFLAGS) ./stopwatch/main.cpp -o build/stopwatch-main
	$(CXX) $(CFLAGS) ./stopwatch/movetest.cpp -o build/movetest
	$(CXX) $(CFLAGS) ./stopwatch/string-test.cpp -o build/string-test
	$(CXX) $(CFLAGS) ./stream_insert_iterators/insert_iterator.cpp -o build/insert_iterator
	$(CXX) $(CFLAGS) ./stream_insert_iterators/stream_iterator.cpp -o build/stream_iterator
	$(CXX) $(CFLAGS) ./templates/template-class.cpp -o build/template-class
	$(CXX) $(CFLAGS) ./templates/template-class2.cpp -o build/template-class2
	$(CXX) $(CFLAGS) ./templates/template-class3.cpp -o build/template-class3
	$(CXX) $(CFLAGS) ./templates/template-function.cpp -o build/template-function
	$(CXX) $(CFLAGS) ./templates/template-inst.cpp -o build/template-inst
	$(CXX) $(CFLAGS) ./templates/template-pointer.cpp -o build/template-pointer
	$(CXX) $(CFLAGS) ./templates/template-spec.cpp -o build/template-spec
	$(CXX) $(CFLAGS) ./templates/template-template.cpp -o build/template-template
	$(CXX) $(CFLAGS) ./templates/template-type.cpp -o build/template-type
	$(CXX) $(CFLAGS) ./templates/template-union.cpp -o build/template-union
	$(CXX) $(CFLAGS) ./thread/async_test4.cpp -o build/async_test4
	$(CXX) $(CFLAGS) ./thread/atomic.cpp -o build/atomic
	$(CXX) $(CFLAGS) ./thread/detach.cpp -o build/detach
	$(CXX) $(CFLAGS) ./tilemap/main.cpp -o build/tilemap-main
#	$(CXX) $(CFLAGS) ./tilemap/newtilemap/newtilemap/newtilemap/main.cpp -o build/main
#	$(CXX) $(CFLAGS) ./tilemap/newtilemap/newtilemap/newtilemap/sdltest/test.cpp -o build/test
#	$(CXX) $(CFLAGS) ./tilemap/TileMap2/main.cpp -o build/main
	$(CXX) $(CFLAGS) ./trim_lines/triml.cpp -o build/triml
#	$(CXX) $(CFLAGS) ./trim_lines/triml.cpp.txt -o build/triml.cpp
	$(CXX) $(CFLAGS) ./typeid/typeid_test2.cpp -o build/typeid_test2
	$(CXX) $(CFLAGS) ./UNIX/forktest/forktest.cpp -o build/forktest
	$(CXX) $(CFLAGS) ./UNIX/pthread/pthread-test.cpp -o build/pthread-test
	$(CXX) $(CFLAGS) ./allocator/al.cc -o build/al
	$(CXX) $(CFLAGS) ./array/ar.cc -o build/ar
	$(CXX) $(CFLAGS) ./array/ar2.cc -o build/ar2
	$(CXX) $(CFLAGS) ./auto/autotest.cc -o build/autotest
	$(CXX) $(CFLAGS) ./bitset/bitset_test.cc -o build/bitset_test
	$(CXX) $(CFLAGS) ./cast/casttest.cc -o build/casttest
	$(CXX) $(CFLAGS) ./chrono/looptest.cc -o build/looptest
	$(CXX) $(CFLAGS) ./chrono/scoped_t.cc -o build/scoped_t
	$(CXX) $(CFLAGS) ./chrono/timetest.cc -o build/timetest
	$(CXX) $(CFLAGS) ./constexpr/constexpr-test.cc -o build/constexpr-test
	$(CXX) $(CFLAGS) ./constexpr/constexpr.cc -o build/constexpr
	$(CXX) $(CFLAGS) ./enum/enum.cc -o build/enum
	$(CXX) $(CFLAGS) ./finally/finally.cc -o build/finally
	$(CXX) $(CFLAGS) ./friend/friend_test.cc -o build/friend_test
	$(CXX) $(CFLAGS) ./fstream/readwrite.cc -o build/readwrite
	$(CXX) $(CFLAGS) ./fstream/textoutput.cc -o build/textoutput
	$(CXX) $(CFLAGS) ./function_syntax/function_syntax.cc -o build/function_syntax
	$(CXX) $(CFLAGS) ./function_syntax/test1.cc -o build/test1
	$(CXX) $(CFLAGS) ./generic/temp1.cc -o build/temp1
	$(CXX) $(CFLAGS) ./generic/temp2.cc -o build/temp2
	$(CXX) $(CFLAGS) ./hero/main.cc -o build/hero-main
	$(CXX) $(CFLAGS) ./init/init_list.cc -o build/init_list
	$(CXX) $(CFLAGS) ./lambda/lambda.cc -o build/lambda
	$(CXX) $(CFLAGS) ./lambda/lambda2.cc -o build/lambda2
	$(CXX) $(CFLAGS) ./lambda/lambda_capture.cc -o build/lambda_capture
	$(CXX) $(CFLAGS) ./lambda/main.cc -o build/lambda-main
	$(CXX) $(CFLAGS) ./lambda/source.cc -o build/source
	$(CXX) $(CFLAGS) ./lambda/test.cc -o build/test
	$(CXX) $(CFLAGS) ./m3ugen/main.cc -o build/m3ugen-main
	$(CXX) $(CFLAGS) ./member/memberdecl.cc -o build/memberdecl
	$(CXX) $(CFLAGS) ./move/move_test.cc -o build/move_test
	$(CXX) $(CFLAGS) ./move/move_test2.cc -o build/move_test2
	$(CXX) $(CFLAGS) ./move/move_test3.cc -o build/move_test3
	$(CXX) $(CFLAGS) ./mutable/mut.cc -o build/mut
	$(CXX) $(CFLAGS) ./namespace/inline_namespace_ex.cc -o build/inline_namespace_ex
	$(CXX) $(CFLAGS) ./operator/default.cc -o build/default
	$(CXX) $(CFLAGS) ./operator/operator.cc -o build/operator
	$(CXX) $(CFLAGS) ./operator/plus.cc -o build/plus
	$(CXX) $(CFLAGS) ./override/override_test.cc -o build/override_test
	$(CXX) $(CFLAGS) ./override/virtual_base.cc -o build/virtual_base
	$(CXX) $(CFLAGS) ./persist/persist.cc -o build/persist
	$(CXX) $(CFLAGS) ./persist/persist-vector-main.cpp -o build/persist-vec-test
	$(CXX) $(CFLAGS) ./pool/driver.cc -o build/driver
	$(CXX) $(CFLAGS) ./random/r.cc -o build/r
	$(CXX) $(CFLAGS) ./random/shuffle.cc -o build/shuffle
	$(CXX) $(CFLAGS) ./random/shuffle2.cc -o build/shuffle2
	$(CXX) $(CFLAGS) ./regex/regex_test.cc -o build/regex_test
	$(CXX) $(CFLAGS) ./rename_files/file_rename.cc -o build/file_rename
	$(CXX) $(CFLAGS) ./smart_pointer/unique.cc -o build/unique
	$(CXX) $(CFLAGS) ./stringstream/iss.cc -o build/iss
	$(CXX) $(CFLAGS) ./stringstream/iss2.cc -o build/iss2
	$(CXX) $(CFLAGS) ./stringstream/ss.cc -o build/ss
	$(CXX) $(CFLAGS) ./symbol_table/symbol_table.cc -o build/symbol_table
	$(CXX) $(CFLAGS) ./test/static_assert_test.cc -o build/static_assert_test
	$(CXX) $(CFLAGS) ./test/temp_test.cc -o build/temp_test
	$(CXX) $(CFLAGS) ./test/temp_test2.cc -o build/temp_test2
	$(CXX) $(CFLAGS) ./test/test.cc -o build/test
	$(CXX) $(CFLAGS) ./test/test2.cc -o build/test2
	$(CXX) $(CFLAGS) ./test/typearr.cc -o build/typearr
	$(CXX) $(CFLAGS) ./thought.cc -o build/thought
	$(CXX) $(CFLAGS) ./thread/async_test.cc -o build/async_test
	$(CXX) $(CFLAGS) ./thread/async_test2.cc -o build/async_test2
	$(CXX) $(CFLAGS) ./thread/async_test3.cc -o build/async_test3
	$(CXX) $(CFLAGS) ./thread/promise.cc -o build/promise
	$(CXX) $(CFLAGS) ./thread/thread_test.cc -o build/thread_test
	$(CXX) $(CFLAGS) ./transfer/transfer.cc -o build/transfer
	$(CXX) $(CFLAGS) ./try/try.cc -o build/try
	$(CXX) $(CFLAGS) ./try/try2.cc -o build/try2
	$(CXX) $(CFLAGS) ./tuple/t.cc -o build/t
	$(CXX) $(CFLAGS) ./typeid/typeid_test.cc -o build/typeid_test
	$(CXX) $(CFLAGS) ./unordered_map/print_recursive.cc -o build/print_recursive
	$(CXX) $(CFLAGS) ./unordered_map/unordered_map_test.cc -o build/unordered_map_test
	$(CXX) $(CFLAGS) ./variadic/v.cc -o build/v
	$(CXX) $(CFLAGS) ./variadic/v2.cc -o build/v2
	$(CXX) $(CFLAGS) ./vector/em.cc -o build/em
	$(CXX) $(CFLAGS) ./vector/persist_vector.cc -o build/persist_vector
clean:
	rm -f build/*
