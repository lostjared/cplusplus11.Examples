
/* Adapted from "The Linux Programming Interface" Chapter 19 Listing 19-1 on page 382 */


#include<iostream>
#include<string>
#include<sys/inotify.h>
#include<fcntl.h>
#include<limits.h>
#include<cstdint>
#include<unistd.h>
constexpr int BUFFER_LENGTH = (10 * ( sizeof(struct inotify_event) + NAME_MAX + 1));

void printNotify(inotify_event *e);
std::string maskToString(uint32_t mask);


int main(int argc, char **argv) {
    
    int nfd_, wd_, i;
    char buffer[BUFFER_LENGTH] __attribute__((aligned(8)));
    ssize_t readBytes;
    char *ptr;
    inotify_event *e;
    
    if(argc < 2) {
        std::cerr << "Error requires at least one argument..\n" << argv[0] << " files\n";
        exit(EXIT_FAILURE);
    }
    
    nfd_ = inotify_init();
    if(nfd_ == -1) {
        std::cerr << "Error on inotify_init.\n";
        exit(EXIT_FAILURE);
    }
    
    for(i = 1; i < argc; ++i) {
        wd_ = inotify_add_watch(nfd_, argv[i], IN_ALL_EVENTS);
        if(wd_ == -1) {
            std::cerr << "Couldn't watch file/directory: " << argv[i] << "\n";
            exit(EXIT_FAILURE);
        }
        std::cout << "Now watching: " << argv[i] << " on descriptor: " << wd_ << "\n";
    }
    
    while(1) {
        
        readBytes = read(nfd_, buffer, BUFFER_LENGTH);
        if(readBytes == 0) {
            std::cerr << "Error on read: \n";
            exit(EXIT_FAILURE);
        }
        
        if(readBytes == -1) {
            std::cerr << "Failure to read..\n";
            exit(EXIT_FAILURE);
        }
        
        std::cout << "Read " << readBytes << " from inotify file descriptor..\n";
        
        for(ptr = buffer; ptr < buffer + readBytes; ) {
            e = (inotify_event *) ptr;
            printNotify(e);
            ptr += sizeof(inotify_event) + e->len;
        }
        
    }
    
    return EXIT_SUCCESS;
}


void printNotify(inotify_event *e) {
    
    std::cout << "Watched directory: " << e->wd << "\n";
    if(e->cookie > 0) std::cout << "Cookie: " << e->cookie << "\n";
    std::cout << "the Mask is: " << maskToString(e->mask) << "\n";
    if(e->len > 0) std::cout << "name: " << e->name;
}

std::string maskToString(uint32_t mask) {
    if(mask & IN_ACCESS) return "IN_ACCESS";
    if(mask & IN_ATTRIB) return "IN_ATTRIB";
    if(mask & IN_CLOSE_NOWRITE) return "IN_CLOSENOWRITE";
    if(mask & IN_CLOSE_WRITE) return "IN_CLOSEWRITE";
    if(mask & IN_CREATE) return "IN_CREATE";
    if(mask & IN_DELETE) return "IN_DELETE";
    if(mask & IN_DELETE_SELF) return "IN_DELETE_SELF";
    if(mask & IN_IGNORED) return "IN_IGNORED";
    if(mask & IN_ISDIR) return "IN_ISDIR";
    if(mask & IN_MODIFY) return "IN_MODIFY";
    if(mask & IN_MOVE_SELF) return "IN_MOVE_SELF";
    if(mask & IN_MOVED_FROM) return "IN_MOVE_FROM";
    if(mask & IN_MOVED_TO) return "IN_MOVED_TO";
    if(mask & IN_OPEN) return "IN_OPEN";
    if(mask & IN_Q_OVERFLOW) return "IN_Q_OVERFLOW";
    if(mask & IN_UNMOUNT) return "IN_UNMOUNT";
       
    return "Unknown..";
}
