#include<iostream>
#include<unistd.h>
#include<sys/wait.h>


int main() {
    
    
    std::cout << "Fork test\n";
  
    pid_t rt_value = 0;
    
    rt_value = fork();
    
    if(rt_value == 0) {
        std::cout << "In Child..\n";
        for(unsigned int i = 0; i < 100; ++i) {
            std::cout << "In Child process. \n";
        }
        std::cout << "Child process done.\n";
        _exit(EXIT_SUCCESS);
        
    } else {
        std::cout << "In Parent..\n";
        for(unsigned int i = 0; i < 100; ++i) {
            std::cout << "In Parent process. \n";
        }
        std::cout << "Parent process done..\n";
    }
    
    int status = 0;
    waitpid(rt_value, &status, 0);
    std::cout << "Suceess!\n";
    return 0;
}
