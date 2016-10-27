/* Adapted from "the Linux Programming Interface"
 Chapter 64
 
 
 */
#include<iostream>
#include<string>
#include"pterm.hpp"

static const int BUF_SIZE=256;
static const int MAX_NAME=1000;
termios orig;

void ttyReset() {
    if(tcsetattr(STDIN_FILENO, TCSANOW, &orig) == -1)
        error("tcsetattr");
}

int main(int argc, char **argv) {
    
    char sname[MAX_NAME];
    const char *shell;
    int m_fd, s_fd;
    winsize ws;
    fd_set in_fds;
    char buf[BUF_SIZE];
    ssize_t bytesRead;
    pid_t cid;
    
    if(tcgetattr(STDIN_FILENO, &orig) == -1)
        error("tcgetattr");
    
    if(ioctl(STDIN_FILENO, TIOCGWINSZ, &ws) < 0)
        error("ioctl");
    
    cid = pty_Fork(&m_fd, sname, MAX_NAME, &orig, &ws);
    if(cid == -1)
        error("pty_Fork");
    if(cid == 0) {
        shell = getenv("SHELL");
        if(shell == NULL || *shell == '\0')
            shell = "/bin/sh";
        
        execlp(shell, shell, (char*) NULL);
        error("execlp");
    }
    
    s_fd = open((argc > 1) ? argv[1] : "typescript", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    if(s_fd == -1)
        error("open typescript");
    
    tty_SetRaw(STDIN_FILENO, &orig);
    if(atexit(ttyReset) != 0)
        error("atexit");
    
    while(1) {
        FD_ZERO(&in_fds);
        FD_SET(STDIN_FILENO, &in_fds);
        FD_SET(m_fd, &in_fds);
        
        if(select(m_fd + 1, &in_fds, NULL, NULL, NULL) == -1)
            error("select");
        
        if(FD_ISSET(STDIN_FILENO, &in_fds)) {
            bytesRead = read(STDIN_FILENO, buf, BUF_SIZE);
            if(bytesRead <= 0)
                exit(EXIT_SUCCESS);
            if(write(m_fd, buf, bytesRead) != bytesRead)
                error("partial write", false);
        }
        
        if(FD_ISSET(m_fd, &in_fds)) {
            bytesRead = read(m_fd, buf, BUF_SIZE);
            if(bytesRead <= 0)
                exit(EXIT_SUCCESS);
            if(write(STDOUT_FILENO, buf, bytesRead) != bytesRead)
                error("partial/failed write\n", false);
            if(write(s_fd, buf, bytesRead) != bytesRead)
                error("partial/failed write\n", false);
        }
    }
        
    
    
    
    return 0;
}
