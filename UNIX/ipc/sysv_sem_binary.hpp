/* Adapted from "the Linux Programming Interface"
 	Chapter 47 page 990
 
 	I was not very familar with these topics so this is
    more like the book than the others.
 
 */

#ifndef __SYSV_SEM_BINARY_H___
#define __SYSV_SEM_BINARY_H___

#include<sys/types.h>
#include<sys/sem.h>


#ifdef __linux__

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
    struct seminfo * __buf;
};

#endif

static bool semUndo = false;
static bool retry = true;

int initSemAvailable(int sid, int snum) {
    union semun arg;
    arg.val = 1;
    return semctl(sid, snum, SETVAL, arg);
    
}

int initSemInUse(int sid, int snum) {
    union semun arg;
    arg.val = 0;
    return semctl(sid, snum, SETVAL, arg);
}

int reserveSem(int sid, int snum) {
    struct sembuf ops;
    ops.sem_num = snum;
    ops.sem_op = -1;
    ops.sem_flg = (semUndo == true) ? SEM_UNDO : 0;
    
    while(semop(sid, &ops, 1) == -1)
        if(errno != EINTR || !retry)
            return -1;
    
    return 0;
}

int releaseSem(int sid, int snum) {
    struct sembuf ops;
    ops.sem_num = snum;
    ops.sem_op = 1;
    ops.sem_flg = (semUndo == true) ? SEM_UNDO : 0;
    return semop(sid, &ops, 1);
}

#endif
