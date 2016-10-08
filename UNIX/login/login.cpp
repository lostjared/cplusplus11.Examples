#define _GNU_SOURCE
#include<ctime>
#include<utmpx.h>
#include<paths.h>
#include<iostream>
#include<iomanip>
#include<errno.h>
#include<cstring>
#include<string>

void error(const std::string &text);
std::string ut_type(utmpx *u);

const int space = 10;

int main(int argc, char **argv) {
    
    if(argc > 1)
        if(utmpxname(argv[1]) == -1)
            error("utmpxname");
    
    setutxent();
    
    std::cout << std::setw(space) << "User" << std::setw(space) << "type" << std::setw(space) << "PID" <<
    std::setw(space) << "line" << std::setw(space) << "id" << std::setw(space*3) << "host" << std::setw(space*3) << "Date/Time\n";
    
    utmpx *u;
    
    while ((u = getutxent()) != NULL) {
        std::cout << std::setw(space) << u->ut_user;
        std::cout << std::setw(space) << ut_type(u);
        std::cout << std::setw(space) << (long) u->ut_pid <<
        std::setw(space) << u->ut_line << std::setw(space) << u->ut_id << std::setw(space*3) << u->ut_host <<
        std::setw(space*3) << ctime((time_t *) &(u->ut_tv.tv_sec));
    }
    endutxent();
    
    return EXIT_SUCCESS;
}

void error(const std::string &text) {
    std::cerr << "Error: " << text << " " << strerror(errno) << "\n";
    exit(EXIT_FAILURE);
}

std::string ut_type(utmpx *u) {
    switch(u->ut_type) {
        case EMPTY: return "EMPTY";
        case RUN_LVL: return "RUN_LVL";
        case BOOT_TIME: return "BOOT_TIME";
        case NEW_TIME: return "NEW_TIME";
        case OLD_TIME: return "OLD_TIME";
        case INIT_PROCESS: return "INIT_PR";
        case LOGIN_PROCESS: return "LOGIN_PR";
        case USER_PROCESS: return "USER_PR";
        case DEAD_PROCESS: return "DEAD_PR";
    }
    return "???";
}
