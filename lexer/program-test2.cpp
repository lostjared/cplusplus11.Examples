#include<iostream>
#include "mxl.hpp"



int main(int argc, char **argv) {
    
    using namespace mxl;
    
    if(argc != 2) { std::cerr << argv[0] << ": requires argument of file.\n"; }
    
    MXLFile file(argv[1]);
    try {
        
        if(file.parse()) {
            while(true) {
                std::string s;
                std::cout << "Enter tag name (enter 0 to quit): ";
                std::getline(std::cin, s);
                if(s == "0") {
                    break;
                }
                std::string tag_name = s;
                std::cout << "Enter tag id: ";
                std::getline(std::cin, s);
                std::string tag_id = s;
                std::cout << "Enter tag value: ";
                std::getline(std::cin, s);
                file(tag_name, tag_id) = s;
            }
            file.outputTags(argv[1]);
        }
        else {
            std::cout << "Error parsing file..\n";
        }
        
    }
    catch(MXL_File_Error &e) {
        std::cerr << "Error: " << e.getError() << "\n";
    }
    catch(...) {
        std::cerr << "Error\n";
    }
    
    
    return 0;
}