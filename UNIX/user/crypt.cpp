#define _XOPEN_SOURCE
#include<iostream>
#include<unistd.h>

int main() {
    char *password = getpass("Enter Password: ");
    char *encrypted = crypt(password, "0x"); // encrypt password one way
    for(char *p = password; *p != 0; ++p) *p = '\0';
    std::cout << "Password encrypted is: " << encrypted << "\n";
    return 0;
}
