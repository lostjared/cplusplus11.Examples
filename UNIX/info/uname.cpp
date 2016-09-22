#include<iostream>
#include<sys/utsname.h>
#include<unistd.h>
#include<cstring>
#include<errno.h>

int main() {
    
    utsname uts;
    
    if(uname(&uts) == -1) {
        std::cerr << "Error on uname: " << strerror(errno) << "\n";
        exit(EXIT_FAILURE);
    }
    
    std::cout << "Node: " << uts.nodename << "\nSystem: " << uts.sysname << "\nRelease: " << uts.release << "\nVersion: " << uts.version << "\nMachine: " << uts.machine << "\n";
    
    return EXIT_SUCCESS;
}
