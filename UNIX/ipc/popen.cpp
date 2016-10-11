#include<iostream>
#include<cstdio>

int main(int argc, char **argv) {
    
    FILE *fptr = popen("ps -A", "r");
    
    if(!fptr) {
        std::cerr << "Error opening program: ps\n";
        exit(EXIT_FAILURE);
    }
    
    while(!feof(fptr)) {
        char buf[1024];
        ssize_t r = fread(buf, 1, 1024, fptr);
        if(r > 0) {
            buf[r] = 0;
            std::cout << buf << "\n";
        }
    }
    
    pclose(fptr);
    
    return 0;
}
