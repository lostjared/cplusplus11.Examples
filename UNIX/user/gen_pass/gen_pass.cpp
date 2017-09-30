#define _XOPEN_SOURCE
#include<iostream>
#include<string>
#include<unistd.h>

int main(int argc, char **argv) {
    char *pw = getpass("Enter password: ");
    std::string ent = getpass("Enter site: ");
    char *encrypted_start = crypt(pw, ent.c_str());
    for(char *p = pw; *p != 0; p++) *p = 0;
    std::cout << "Password: " << encrypted_start << "\n";
    return 0;
}
