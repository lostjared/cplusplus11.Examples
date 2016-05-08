/* C++11 Example reading/writing text to a file
 
 run the program the following way
 
 ./text-test -r sourcefile.txt
 
 will read sourcefile and output to stdout
 
 ./text-test -o sourcefile.txt
 
 will prompt for input and echo to sourcefile.txt
 
 */

#include<iostream>
#include<fstream>
#include<string>
#include<vector>

class ReadError {};


std::string readFile(std::string filename) {
    std::string value;
    std::fstream file;
    file.open(filename, std::ios::in);
    
    if(!file.is_open()) {
        throw ReadError();
    }
    
    file.seekg(0, std::ios::end);
    size_t len = file.tellg();
    file.seekg(0, std::ios::beg);
    char *text = 0;
    
    try {
     text = new char [len+1];
     file.read(text, len);
    } catch(...) {
        if(text != 0) delete [] text;
        file.close();
        throw ReadError();
    }
    
    file.close();
    value = text;
    delete [] text;
    return value;
}


int main(int argc, char **argv) {
    
    if(argc == 3 && std::string(argv[1]) == "-r") {
        // read file
        try {
            std::string text;
            text = readFile(argv[2]);
            std::cout << text << "\n";
            // use text
            return 0;
        } catch(ReadError) {
            std::cerr << "Error could not read file.\n";
            return -1;
        }
    }
    if(argc == 3 && std::string(argv[1]) == "-o") {
        // get string
        std::string s;
        std::getline(std::cin, s);

        // output string
        std::fstream file;
        file.open(argv[2], std::ios::out);
        file << s;
        file.close();
    }

    std::cout << argv[0] << "\n -r readfile.txt\n -o writefile.txt\n\n";
    
    return 0;
}

