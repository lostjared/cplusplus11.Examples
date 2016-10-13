/* Adapted from "the Linux Programming Interface"
   Chapter 48 page 1002
 
 I was not very familar with these topics so this is
 more like the book than the others.
  
*/


#ifndef __SYSV_SM__HPP_
#define __SYSV_SM__HPP_

#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/sem.h>
#include<sys/shm.h>
#include "sysv_sem_binary.hpp"

const int SHM_KEY = 0xDEADBEEF;
const int SEM_KEY = 0x012456;

const int IO_PERM = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP;


const int WRITE_SEM = 0;
const int READ_SEM = 1;

#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif

struct shmseg {
    int cnt;
    char buf[BUF_SIZE];
};

#endif
