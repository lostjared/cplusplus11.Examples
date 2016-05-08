#include<iostream>
#include<fstream>
#include<vector>


std::fstream file;
std::vector<std::string> log;

// using universal reference can either be T& or T&&
// Note: Page 178 Effective Modern C++
template<typename T>
void LogToFile(T&& value) {
    file << value;
    log.emplace_back(std::forward<T>(value));
}



int main(int argc, char **argv) {
    
    try {
        file.open("test.dat", std::ios::out);
        if(!file.is_open()) {
            std::cerr << "Could not open file..\n";
            return -1;
        }
        
        std::string str;
        for(unsigned int i = 0; i < 500; ++i) {
            str += "0000000\n";
        }

        LogToFile(std::string("Using string\n"));
        
        LogToFile(std::move(str));
        
        LogToFile("Program initalized..\n");
        LogToFile("Using Universal Reference..\n");
        
        
        for(auto &i : log) {
            std::cout << i;
        }
        
    }
    catch(...) {
        std::cerr << "Error occured.\n";
    }
    
    
    file.close();
    
    return 0;
}