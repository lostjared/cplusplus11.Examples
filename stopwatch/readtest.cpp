#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include"stopwatch.hpp"


void read_rd(const std::string &text) {
    StopWatch<HighResolutionClock> timer("read rdbuff");
    std::fstream file;
    file.open(text, std::ios::in);
    if(!file.is_open()) {
        std::cerr << "Error opening file: " << text << "\n";
        exit(0);
        return;
    }
    std::ostringstream stream;
    stream << file.rdbuf();
    std::cout << stream.str().length() << " bytes.\n";
    file.close();
}

void read_read(const std::string &text) {
    
    StopWatch<HighResolutionClock> timer("read with read member function");
    std::fstream file;
    file.open(text, std::ios::in|std::ios::binary);
    if(!file.is_open()) {
        std::cerr << "Error opening file: " << text << "\n";
        exit(0);
        return;
    }
    file.seekg(0, std::ios::end);
    int length = file.tellg();
    file.seekg(0, std::ios::beg);
    char *tmp = new char [length+1];
    file.read(tmp, length);
    std::string textv;
    textv = tmp;
    delete [] tmp;
    std::cout << textv.length() << " bytes.\n";
    file.close();
}


int main(int argc, char **argv) {
    

    if(argc != 2) {
        std::cerr << "argument required text file to read.\n";
        exit(0);
    }
    
    read_rd(argv[1]);
    read_read(argv[1]);
    
    return 0;
}