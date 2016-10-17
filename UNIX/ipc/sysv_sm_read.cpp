
/* Adapted from "the Linux Programming Interface"
 Chapter 48 page 1005
 
 I was not very familar with these topics so this is
 more like the book than the others.
 
 */

#include<iostream>
#include<string>
#include<cstring>
#include<errno.h>
#include"sysv_sm.hpp"

void error(const std::string &text);

int main(int argc, char **argv) {
    
    int semid, shmid, xfrs, bytes;
    struct shmseg *s;
    
    semid = semget(SEM_KEY, 0, 0);
    if(semid == -1)
        error(strerror(errno));
    shmid = shmget(SHM_KEY, 0, 0);
    if(shmid == -1)
        error(strerror(errno));
    
    s = (struct shmseg *)shmat(shmid, NULL, SHM_RDONLY);
    if(s == (void*) -1)
        error(strerror(errno));
    
    for(xfrs = 0, bytes = 0; ; xfrs++) {
        if(reserveSem(semid, READ_SEM) == -1)
            error("reserveSem");
        if(s->cnt == 0)
            break;
        bytes += s->cnt;
        
        if(write(STDOUT_FILENO, s->buf, s->cnt) != s->cnt)
            error("partial write error");
        if(releaseSem(semid, WRITE_SEM) == -1)
            error("releaseSem");
    }
    
    if(shmdt(s) == -1)
        error("shmdt");
    if(releaseSem(semid, WRITE_SEM) == -1)
        error("releaseSem");
    
    std::cerr << "Got " << bytes << " bytes (" << xfrs << " xfrs)\n";
    return EXIT_SUCCESS;
}


void error(const std::string &text) {
    std::cerr << "Error: " << text << "\n";
    exit(EXIT_FAILURE);
}
