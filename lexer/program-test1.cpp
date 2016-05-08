#include"mxl.hpp"
#include<iostream>
#include<string>
#include<unordered_map>



int main(int argc, char **argv) {
    
    if(argc != 2) { std::cerr << "Requires 1 argument.\n"; exit(0); }

    try {
        mxl::MXLFile mxl_file(argv[1]);
        if(mxl_file.parse()) {
            mxl_file.printTags(std::cout);
            std::cout << "Print out just tag variable names\n";
            for(auto i = mxl_file.begin(); i != mxl_file.end(); ++i) {
                std::cout << i->first << "\n";
            }
            std::cout << "Adding tag\n";
            mxl_file.tag_Set("Pointer", "z", "100");
            std::cout << "Outputing new tag file..\n";
            mxl_file.outputTags("temp.mxl");
        }

    } catch(mxl::MXL_File_Error &e) {
        e.printError(std::cerr);
        exit(0);
    }
    
    return 0;
}