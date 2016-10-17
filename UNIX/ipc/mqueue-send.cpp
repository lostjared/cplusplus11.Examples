/* Adapted from "the Linux Programming Interface"
 Chapter 52
 */
#include<mqueue.h>
#include<iostream>
#include<cstring>

int main(int argc, char **argv) {
  
    if(argc != 3) {
        std::cerr << "Error requires two arguments\n" << argv[0] << "path prority\n";
        exit(EXIT_FAILURE);
    }
    
    int prio = atoi(argv[2]);
    
    mqd_t mqd;
    mqd = mq_open(argv[1], O_CREAT | O_WRONLY);
    if(mqd == (mqd_t) -1) {
        std::cerr << "Error failed to open queue.\n";
        exit(EXIT_FAILURE);
    }
    
    char buffer[1024];
    std::cin >> buffer;
    
    if(mq_send(mqd, buffer, strlen(buffer), prio) == -1) {
        std::cerr << "Error sending message..\n";
    }

    return 0;
}
