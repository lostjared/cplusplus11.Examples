/*
 
 from MAN page: $ man vfork
 
 vfork() can be used to create new processes without fully copying the address space of the old process, which is horrendously inefficient in a paged environment.  It
 is useful when the purpose of fork(2) would have been to create a new system context for an execve.  vfork() differs from fork in that the child borrows the parent's
 memory and thread of control until a call to execve(2) or an exit (either by a call to exit(2) or abnormally.)  The parent process is suspended while the child is
 using its resources.
 
 */


#include<iostream>
#include<string>
#include<cstring>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<errno.h>

void error(std::string text) {
    std::cerr << text << ": " << strerror(errno) << "\n";
    exit(EXIT_FAILURE);
}

int main() {
    std::cout << "Program started...\n";
    pid_t id;
    switch ((id = vfork())) { // do not inherit address space from parent
        case -1:
            std::cerr << "Error on vfork..\n";
            break;
        case 0:
            // print directory
            execl("/bin/sh", "sh", "-c", "ls", (char*) 0); // replace child with program
            error("Error on execl");// never gets here unless error
            break;
        default:
            break;
    }
    waitpid(id, 0, 0);
    std::cout << "Listed directory..\n";
    exit(EXIT_SUCCESS);
    return 0;
}
