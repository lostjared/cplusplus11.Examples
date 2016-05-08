/*
 read two files at the same time 
 synchrnoize with std::future
 takes two arguments each of a text file
 
*/

#include<iostream>
#include<thread>
#include<future>
#include<vector>
#include<fstream>

void readList(char c, std::vector<std::string> &v, const char *srcFile) {
    std::fstream file;
    file.open(srcFile, std::ios::in);
    if(!file.is_open()) {
        std::cerr << "Error could not open file.\n";
        return;
    }
    while(!file.eof()) {
        std::string str;
        std::getline(file, str);
        if(file) {
            v.push_back(str);
            std::cout.put(c).flush();
        }
    }
    file.close();
}

void outputList(std::vector<std::string> &v) {
    for(auto &i : v) {
        std::cout << i << "\n";
    }
}

int main(int argc, char **argv) {
    if(argc != 3) {
        std::cerr << "Error requires two arguments.\n";
        return -1;
    }
    std::vector<std::string> file_strings1;
    std::vector<std::string> file_strings2;
    std::cout << "+ for reading of file1\n* for reading of file2\n";
    std::future<void> list1 = std::async([&](){ readList('+', file_strings1, argv[1]); });
    
    readList('*', file_strings2, argv[2]);
    list1.wait();
    std::cout << "\nList1: ";
    outputList(file_strings1);
    std::cout << "\nList2: ";
    outputList(file_strings2);
    return 0;
}