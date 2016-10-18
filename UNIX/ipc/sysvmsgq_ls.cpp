#include<iostream>
#include<sys/types.h>
#include<sys/msg.h>
#include<sys/ipc.h>
#include<unistd.h>
#include<cstdio>
#include<cstring>
#include<errno.h>
#include<iomanip>

void error(const std::string &text);

int main(int argc, char **argv) {
    
    int max, i, id_msq;
    msqid_ds ds;
    msginfo _msginfo;
    
    max = msgctl(0, MSG_INFO, (struct msqid_ds *)&_msginfo);
    
    if(max == -1)
        error("msgctl_msg_info");
    
    std::cout << "Maximum: " << max << "\n\n";
    std::cout << "Index     id       key      messages\n";
    
    for(i = 0; i < max; ++i) {
        id_msq = msgctl(i, MSG_STAT, &ds);
        if(id_msq == -1) {
            if(errno != EINVAL && errno != EACCES)
                std::cerr << "Error accessing queue..\n";
            continue;
        }
        
        std::cout << std::left << std::setw(5) << i << std::setw(5) << id_msq
        << std::setw(5) << (unsigned long)ds.msg_perm.__key << std::setw(5) << (long) ds.msg_qnum << "\n";
    }
    
    exit(EXIT_SUCCESS);
    return 0;
}


void error(const std::string &text) {
    std::cerr << "Error: " << text << " " << strerror(errno) << "\n";
}
