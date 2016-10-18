/* Adapted from "the Linux Programming Interface"
 Chapter 53
 */
#include<mqueue.h>
#include<iostream>
#include<unistd.h>
#include<errno.h>
#include<cstring>
#include<fcntl.h>

int main(int argc, char **argv) {
    mqd_t mqd;
    mode_t perms;
    mq_attr attr;
    int flags;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = 2048;
    flags = O_RDWR | O_CREAT;
    perms = S_IRUSR | S_IWUSR;
    mqd = mq_open(argv[1], flags, perms, &attr);
    if(mqd == (mqd_t) -1) {
        std::cerr << "Error creating queue.\n" << strerror(errno) << "\n";
        exit(EXIT_FAILURE);
    }
    return EXIT_SUCCESS;
}
