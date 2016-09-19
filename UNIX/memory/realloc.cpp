#include<iostream>
#include<cstdlib>

int main() {
    char *buf = (char*)realloc(NULL, sizeof(char) * 12); // initial alloc
    snprintf(buf, 12, "Hello World");
    std::cout << "initial alloc: " << "12 bytes..\n buf is: " << buf << "\n";
    char *nbuf = (char*)realloc(buf, sizeof(char) * 25); // resize memory buffer
    snprintf(nbuf, 25, "%s :) Resized", nbuf);
    std::cout << "after realloc: " << "25 bytes..\n buf is: " << nbuf << "\n";
 
    free(nbuf); // release memory
    return 0;
}
