#include<iostream>
#include<pwd.h>
#include<grp.h>

int main() {
    
    
    passwd *pwd;
    
    while((pwd = getpwent()) != NULL) {
        std::cout << "user: " << pwd->pw_name << " id: " << pwd->pw_uid << "\n";
    }
    
    endpwent();
    
    return 0;
}
