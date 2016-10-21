CXX_FLAGS=-std=c++11 -Wall

all: popen-test pipe-test sysv-sm-read sysv-sm-write fifo-server fifo-client posix-sem-create posix-sem-unlink posix-sem-wait posix-sem-post posix-sem-thread mmap-test posix-shm-create posix-shm-read posix-shm-write posix-shm-unlink



popen-test: popen.cpp
	$(CXX) $(CXX_FLAGS) popen.cpp -o popen-test

pipe-test: pipe.cpp
	$(CXX) $(CXX_FLAGS) pipe.cpp -o pipe-test

#sysvmsgq-ls: sysvmsgq_ls.cpp
#	$(CXX) $(CXX_FLAGS) sysvmsgq_ls.cpp -o sysvmsgq-ls

sysv-sm-read: sysv_sm_read.cpp sysv_sem_binary.hpp sysv_sm.hpp
	$(CXX) $(CXX_FLAGS) sysv_sm_read.cpp -o sysv-sm-read

sysv-sm-write: sysv_sm_write.cpp sysv_sem_binary.hpp sysv_sm.hpp
	$(CXX) $(CXX_FLAGS) sysv_sm_write.cpp -o sysv-sm-write

fifo-server: fifo-read.cpp
	$(CXX) $(CXX_FLAGS) fifo-read.cpp -o fifo-server

fifo-client: fifo-write.cpp
	$(CXX) $(CXX_FLAGS) fifo-write.cpp -o fifo-client

posix-sem-create: posix-sem-create.cpp
	$(CXX) $(CXX_FLAGS) posix-sem-create.cpp -o posix-sem-create -pthread

posix-sem-unlink: posix-sem-unlink.cpp
	$(CXX) $(CXX_FLAGS) posix-sem-unlink.cpp -o posix-sem-unlink -pthread

posix-sem-post: posix-sem-post.cpp
	$(CXX) $(CXX_FLAGS) posix-sem-post.cpp -o posix-sem-post -pthread
posix-sem-wait: posix-sem-wait.cpp
	$(CXX) $(CXX_FLAGS) posix-sem-wait.cpp -o posix-sem-wait  -pthread

posix-sem-thread: posix-sem-thread.cpp
	$(CXX) $(CXX_FLAGS) posix-sem-thread.cpp -o posix-sem-thread -pthread 

mmap-test: mmap.cpp
	$(CXX) $(CXX_FLAGS) mmap.cpp -o mmap-test

posix-shm-create: posix-shm-create.cpp
	$(CXX) $(CXX_FLAGS) posix-shm-create.cpp -o posix-shm-create -pthread
posix-shm-read: posix-shm-read.cpp
	$(CXX) $(CXX_FLAGS) posix-shm-read.cpp -o posix-shm-read -pthread
posix-shm-write: posix-shm-write.cpp
	$(CXX) $(CXX_FLAGS) posix-shm-write.cpp -o posix-shm-write -pthread

posix-shm-unlink: posix-shm-unlink.cpp
	$(CXX) $(CXX_FLAGS) posix-shm-unlink.cpp -o posix-shm-unlink

clean:
	rm -f popen-test pipe-test sysvmsgq-ls sysv-sm-write sysv-sm-read fifo-server fifo-client posix-sem-create posix-sem-unlink posix-sem-wait posix-sem-post posix-sem-thread mmap-test posix-shm-create posix-shm-read posix-shm-write posix-shm-unlink

