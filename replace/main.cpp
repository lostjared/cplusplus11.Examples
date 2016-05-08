#include"replace.hpp"
#include<fstream>


class FileOpenError {};

std::string readFile(const std::string &filename) {
    std::string temp;
    std::fstream file;
    file.open(filename, std::ios::in);
    if(!file.is_open()) {
        throw FileOpenError();
    }
    
    file.seekg(0, std::ios::end);
    int length = file.tellg();
    file.seekg(0, std::ios::beg);
    
    char *buf = new char [length+1];
    file.read(buf, length);
    temp = buf;
    delete [] buf;
    file.close();
    return temp;
}

void writeFile(const std::string &filename, const std::string &data) {
    std::fstream file;
    file.open(filename, std::ios::out);
    if(!file.is_open()) {
        throw FileOpenError();
    }
    file << data;
    file.close();
}

int main(int argc, char **argv) {
    try {
        if(argc != 4) {
            std::cerr << "Program requires three arguments...\n" << argv[0] << " TextFile search replacement";
            return -1;
        }
        std::string temp_text=readFile(argv[1]);
        std::string replacement=replaceString(temp_text, argv[2], argv[3]);
        std::string filename=argv[1];
        filename += ".replaced";
        writeFile(filename, replacement);
        
    } catch(NotFound) {
        std::cerr << "Error search string not found..\n";
    } catch(FileOpenError) {
        std::cerr << "Couldn't open file..\n";
    }
    
    
    return 0;
}