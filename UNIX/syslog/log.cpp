
/*
 Write to syslog 
 To see the message
 
 $ cat /var/log/system.log

 or 
 
 $ tail -f /var/log/system.log
 
*/
 
#include<syslog.h>
#include<iostream>


int main(int argc, char **argv) {
    if(argc != 2) {
        std::cout << "Error requires one argument..\n";
        exit(EXIT_FAILURE);
    }
    
    openlog(argv[0], LOG_PID | LOG_CONS | LOG_NOWAIT, LOG_LOCAL0);
    syslog(LOG_WARNING, "Syslog test: %s", argv[1]);
    closelog();
    return 0;
}
