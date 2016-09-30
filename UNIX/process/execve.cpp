#include<iostream>
#include<cstring>
#include<unistd.h>
#include<errno.h>

void err(const char *e) {
    std::cerr << "Error: " << strerror(errno) << "\n";
    exit(EXIT_FAILURE);
}

int main() {
    
    const char *argv[] = { "execve", NULL };
    const char *env[] = { NULL };
    
    execve("/bin/bash", (char**)argv, (char**)env);
    err("An Error as Occoured..\n");
    return 0;
}
