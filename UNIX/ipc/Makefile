CXX_FLAGS=-std=c++11 -Wall

all: popen-test pipe-test sysv-sm-read sysv-sm-write


popen-test: popen.cpp
	$(CXX) $(CXX_FLAGS) popen.cpp -o popen-test

pipe-test: pipe.cpp
	$(CXX) $(CXX_FLAGS) pipe.cpp -o pipe-test

#sysvmsgq-ls: sysvmsgq_ls.cpp
#	$(CXX) $(CXX_FLAGS) sysvmsgq_ls.cpp -o sysvmsgq-ls

sysv-sm-read: sysv_sm_read.cpp
	$(CXX) $(CXX_FLAGS) sysv_sm_read.cpp -o sysv-sm-read

sysv-sm-write: sysv_sm_write.cpp
	$(CXX) $(CXX_FLAGS) sysv_sm_write.cpp -o sysv-sm-write

clean:
	rm -f popen-test pipe-test sysvmsgq-ls sysv-sm-write sysv-sm-read
