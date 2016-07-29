#ifndef __SORT_FILES_H__
#define __SORT_FILES_H__

#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<algorithm>

class FileSort {
public:
    FileSort() = default;
    
    bool checkIfWhitespace(std::string s) {
        for(unsigned int i = 0; i < s.length(); ++i) {
            if(s[i] != '\n' && s[i] != '\r' && s[i] != ' ' && s[i] != '\t')
                return true;
        }
        return false;
    }
    
    void addFile(std::string filename) {
        std::fstream file;
        file.open(filename, std::ios::in);
        
        if(!file.is_open()) {
            std::cerr << "Error opening file: " << filename << "\n";
            exit(0);
        }
        while(!file.eof()) {
            std::string s;
            std::getline(file, s);
            if(file && checkIfWhitespace(s))
                items.push_back(s);
        }
        file.close();
    }
    
    void sortAndOutput(std::string filename) {
        std::sort(items.begin(), items.end());
        std::fstream file;
        file.open(filename, std::ios::out);
        if(!file.is_open()) {
            std::cerr << "Error creating file: " << filename << "\n";
            exit(0);
        }
        for(auto &i : items) {
            file << i << "\n";
        }
        file.close();
        std::cout << "Wrote to file: " << filename << " " << items.size() << " items.\n";
    }
    
protected:
    std::vector<std::string> items;
};




#endif
