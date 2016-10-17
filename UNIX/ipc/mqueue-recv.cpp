/* Adapted from "the Linux Programming Interface"
 Chapter 52
 */
#include<mqueue.h>
#include<unistd.h>
#include<fcntl.h>
#include<iostream>

int main(int argc, char **argv ){
    if(argc != 2) {
        std::cerr << "Error requires one argument\n" << argv[0] << " queue\n";
        exit(EXIT_FAILURE);
    }
    mqd_t mqd;
    mqd = mq_open(argv[1], O_RDONLY);
    if(mqd == (mqd_t) -1) {
        std::cerr << "Error openining queue.\n";
    }
    mq_attr attr;
    if(mq_getattr(mqd, &attr) == -1) {
        std::cerr << "Error getting attributes..\n";
        exit(EXIT_FAILURE);
    }
    void *buffer;
    buffer = malloc(attr.mq_msgsize);
    if(buffer == NULL) {
        std::cerr << "Error allocating buffer.\n";
        exit(EXIT_FAILURE);
    }
    ssize_t nBytes;
    unsigned int prio = 0;
    nBytes = mq_receive(mqd, (char*)buffer, attr.mq_msgsize, &prio);
    if(nBytes == -1) {
        std::cerr << "Error reading buffer from queue.\n";
        exit(EXIT_FAILURE);
    }
    std::cout << "Read " << nBytes << " prio: " << prio << " from queue: " << argv[1] << "\n";
    if(write(STDOUT_FILENO, buffer, nBytes) == -1) {
        std::cerr << "Failed to write bytes to stream for output.\n";
        exit(EXIT_FAILURE);
    }
    write(STDOUT_FILENO, "\n", 1);
    return EXIT_SUCCESS;
}
