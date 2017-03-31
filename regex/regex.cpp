#include<iostream>
#include<regex>
#include<string>


int main(int argc, char **argv) {
    
    std::cout << "Enter IP Address: ";
    std::string ip;
    std::getline(std::cin, ip);
    
    if(ip.length() == 0) {
        std::cerr << "Error nothing entered\n";
        exit(EXIT_FAILURE);
    }
    
    std::regex r("(\\d{1,3}(\\.\\d{1,3}){3})");
    bool is_valid = std::regex_match(ip, r);
    if(is_valid)
        std::cout << ip << " is a valid IP address\n";
    else
        std::cout << ip << " is not a valid IP address\n";
    
    return 0;
}
