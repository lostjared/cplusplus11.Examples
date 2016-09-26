/* 
 
 Run this program and use Control+C to
 send the SIGINT signal and it will recgonize this
 to exit the program press Ctrl+/ to send quit signal
 
*/


#include<signal.h>
#include<unistd.h>
#include<iostream>
#include<string>
#include<cstring>

void writeOutput(const char *src) {
    write(1, src, strlen(src)); // printf is not reentrant and not safe
    // for use with a signal, so we use write that is async signal safe
}


void handler(int s) {
    writeOutput(" Signal SIGINT caught\n");
}

int main(int argc, char **argv) {
    
    if(signal(SIGINT, handler) == SIG_ERR) {
        std::cerr << "Error creating signal..\n";
        exit(EXIT_FAILURE);
    }
    
    int index = 0;
    
    while(1) {
        ++index;
        sleep(3);
        std::cout << "index: " << index << "\n";
    }
    
    return 0;
}

