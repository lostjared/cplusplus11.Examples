#include<signal.h>
#include<cctype>
#include<fcntl.h>
#include<termios.h>
#include<iostream>
#include<string>
#include<unistd.h>
#include<cstring>

static volatile sig_atomic_t gotSignal = 0;

int ttySetCbreak(int fd, termios *prevTermios) {
    
    termios t;
    if(tcgetattr(fd, &t) == -1)
        return -1;
    
    if(prevTermios != NULL)
        *prevTermios = t;
    
    t.c_lflag &= ~(ICANON | ECHO);
    t.c_lflag |= ISIG;
    t.c_iflag &= ~ICRNL;
    t.c_cc[VMIN] = 1;
    t.c_cc[VTIME] = 0;
    
    if(tcsetattr(fd, TCSAFLUSH, &t))
        return -1;
    
    return 0;
}


void error(const std::string &text, bool e = true);

void Ready(int s) {
    gotSignal = 1;
}

int main(int argc, char **argv) {
    
    struct sigaction sa;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sa.sa_handler = Ready;
    if(sigaction(SIGIO, &sa, NULL) == -1)
        error("sigaction");
    
    if(fcntl(STDIN_FILENO, F_SETOWN, getpid()) == -1)
        error("fcntl F_SETOWN");
    
    int flags = fcntl(STDIN_FILENO, F_GETFL);
    
    if(fcntl(STDIN_FILENO, F_GETFL, flags | O_ASYNC | O_NONBLOCK) == -1)
        error("fcntl F_GETFL");
    
    termios origtermios;
    
    if(ttySetCbreak(STDIN_FILENO, &origtermios) == -1)
        error("ttySetCbreak", false);
    
    bool complete;
    int counter = 0;
    char ch;
    
    for(complete = false, counter = 0; !complete; counter++) {
        for(int j = 0; j < 100000000; ++j) continue;
        if(gotSignal) {
            gotSignal = 0;
            
            while(read(STDIN_FILENO, &ch, 1) > 0 && !complete) {
                std::cout << "counter: " << counter << " read: " << ch << "\n";
                complete = (ch == '#');
            }
        }
    }
    
    if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &origtermios) == -1)
        error("tcsetattr");
    
    return EXIT_SUCCESS;
}

void error(const std::string &text, bool e) {
    std::cerr << "Error: " << text << "\n";
    if(e) std::cerr << strerror(errno) << "\n";
    exit(EXIT_FAILURE);
}
