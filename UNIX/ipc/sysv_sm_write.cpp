
/* Adapted from "the Linux Programming Interface"
 Chapter 48 page 1003
 
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
    
    int semid, shmid, bytes, xfrs;
    struct shmseg *s;
    union semun d;
    
    semid = semget(SEM_KEY, 2, IPC_CREAT | IO_PERM);
    if(semid == -1)
        error("semget 1");
    
    if(initSemAvailable(semid, WRITE_SEM) == -1)
        error("initSemAvailable");
    if(initSemInUse(semid, READ_SEM) == -1)
        error("initSemInUse");
    
    shmid = shmget(SHM_KEY, sizeof(struct shmseg), IPC_CREAT | IO_PERM);
    if(shmid == -1)
        error("shmget");
    
    s = (struct shmseg *)shmat(shmid, NULL, 0);
    if(s == (void *)-1)
        error("shmat");
    
    for(xfrs = 0, bytes = 0; ; xfrs++, bytes += s->cnt) {
        if(reserveSem(semid, WRITE_SEM) == -1)
            error("reserveSem");
        
        s->cnt = read(STDIN_FILENO, s->buf, BUF_SIZE);
        if(s->cnt == -1)
            error("read");
        
        if(releaseSem(semid, READ_SEM) == -1)
            error("releaseSem");
        
        if(s->cnt == 0)
            break;
        
    }
    
    if(reserveSem(semid, WRITE_SEM) == -1)
        error("reserveSem");
    
    if(semctl(semid, 0, IPC_RMID, d) == -1)
        error("semctl");
    
    std::cerr << "Sent " << bytes << " (" << xfrs << " xfrs)\n";
    
    
    return EXIT_SUCCESS;
}


void error(const std::string &text) {
    std::cerr << "Error: " << text << "\n";
    exit(EXIT_FAILURE);
}
