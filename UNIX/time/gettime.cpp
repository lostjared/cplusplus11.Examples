#include<iostream>
#include<sys/time.h>
#include<ctime>
#include<unistd.h>

int main() {
    
    time_t passed = time(0);
    std::cout << "Unix Epoch: " << passed << " seconds since Thursday January 1, 1970\n";
    
    timeval t;
    gettimeofday(&t, 0);
    std::cout << "Time is at: " << t.tv_sec << ":" << t.tv_usec << "\n";
    std::cout << "Waiting two seconds..\n";
    sleep(2);
    gettimeofday(&t, 0);
    std::cout << "Time is at: " << t.tv_sec << ":" << t.tv_usec << "\n";
    passed = time(0);
    std::cout << "Current: " << ctime(&passed) << "\n";
    tm *time_at;
    time_at = localtime(&passed);
    char buffer[1024];
    size_t s;
    s = strftime(buffer, 1024, "%D", time_at);
    if(s > 0) {
        std::cout << "Date: " << buffer << "\n";
    }
    
    return EXIT_SUCCESS;
}
