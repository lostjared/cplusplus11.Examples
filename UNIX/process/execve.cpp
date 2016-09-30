#include<iostream>
#include<cstring>
#include<unistd.h>
#include<errno.h>

void err(const char *e) {
    std::cerr << "Error: " << strerror(errno) << "\n";
    exit(EXIT_FAILURE);
}

int main() {
    execve("/bin/bash", NULL, NULL);
    err("An Error as Occoured..\n");
    return 0;
}
