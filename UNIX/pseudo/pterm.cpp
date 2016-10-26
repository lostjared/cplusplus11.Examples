
/* Adapted from "the Linux Programming Interface"
 Chapter 64
 
 
 */

#include "pterm.hpp"

static const int MAX_NAME=1000;

void error(const std::string &text, bool err) {
    std::cerr << "Error: " << text << "\n";
    if(err) std::cerr << strerror(errno) << "\n";
    exit(EXIT_FAILURE);
}

int pty_MasterOpen(char *name, size_t len) {
    int m_fd, saved;
    char *p;
    
    m_fd = posix_openpt(O_RDWR | O_NOCTTY);
    if(m_fd == -1)
        return -1;
    
    if(grantpt(m_fd) == -1) {
        saved = errno;
        close(m_fd);
        errno = saved;
        return -1;
    }
    
    if(unlockpt(m_fd) == -1) {
        saved = errno;
        close(m_fd);
        errno = saved;
        return -1;
    }
    
    p = ptsname(m_fd);
    if(p == NULL) {
        saved = errno;
        close(m_fd);
        errno = saved;
        return -1;
    }
    
    if(strlen(p) < len)
        strncpy(name, p, len);
    else {
        close(m_fd);
        errno = EOVERFLOW;
        return -1;
    }
    return m_fd;
}

pid_t pty_Fork(int *m_fd, char *name, size_t len, const termios *st, winsize *s_size) {
    int mfd, sfd, saved;
    pid_t cid;
    char slname[MAX_NAME];
    mfd = pty_MasterOpen(slname, MAX_NAME);
    if(mfd == -1)
        return -1;
    
    if(name != NULL) {
        if(strlen(slname) < len)
            strncpy(name, slname, len);
        else {
            close(mfd);
            errno = EOVERFLOW;
            return -1;
        }
    }
    
    cid = fork();
    if(cid == -1) {
        saved = errno;
        close(mfd);
        errno = saved;
        return -1;
    }
    
    if(cid != 0) {
        *m_fd = mfd;
        return cid;
    }
    
    if(setsid() == -1) {
        std::cerr << "Error: ssid\n";
        _exit(0);
    }
    
    close(mfd);
    sfd = open(slname, O_RDWR);
    if(sfd == -1) {
        std::cerr << "Error open sid\n";
        _exit(0);
    }
#ifdef TIOCSCTTY
    if(ioctl(sfd, TIOCSCTTY, 0) == -1) {
        std::cerr << "Error TIOCSCTTY\n";
        _exit(0);
    }
#endif
    
    if(st != NULL) {
        if(tcsetattr(sfd, TCSANOW, st) == -1) {
            std::cerr << "Error tcsetattr\n";
            _exit(0);
        }
    }
    
    if(s_size != NULL) {
        if(ioctl(sfd, TIOCSWINSZ, s_size) == -1) {
            std::cerr << "Error ioctl\n";
            _exit(0);
        }
    }
    
    if(dup2(sfd, STDIN_FILENO) != STDIN_FILENO) {
        std::cerr << "Error duplicating file descriptor\n";
        _exit(0);
    }
    
    
    if(dup2(sfd, STDOUT_FILENO) != STDOUT_FILENO) {
        std::cerr << "Error duplicating file descriptor\n";
        _exit(0);
    }
    
    if(dup2(sfd, STDERR_FILENO) != STDERR_FILENO) {
        std::cerr << "Error duplicating file descriptor\n";
        _exit(0);
    }
    
    if(sfd > STDERR_FILENO)
        close(sfd);
    
    return 0;
}

int tty_SetRaw(int fd, termios *prev) {
    termios t;
    if(tcgetattr(fd, &t) == -1)
        return -1;
    
    if(prev != NULL)
        *prev = t;
    
    t.c_lflag &= ~(ICANON | ISIG | IEXTEN | ECHO);
    t.c_iflag &= ~(BRKINT | ICRNL | IGNBRK | IGNCR |INLCR | INPCK | ISTRIP | IXON | PARMRK);
    t.c_oflag &= ~OPOST;
    
    t.c_cc[VMIN] = 1;
    t.c_cc[VTIME] = 0;
    
    if(tcsetattr(fd, TCSAFLUSH, &t) == -1)
        return -1;
    
    return 0;
}












