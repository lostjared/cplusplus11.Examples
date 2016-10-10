
/*
 For my friend this should just be a starting place for this program.
 You will want to add include paths and linker paths and linker options
 
 to execute
 
 ./compile-test "sourcefile1.cpp sourcefile2.cpp" output_exe
 
 if MSDN is correct on windows it should be _popen.

*/
 

#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<cstdio>
#include<cstdlib>
#ifndef PATH_MAX
#define PATH_MAX        4096
#endif

// the compile function
bool compile(std::string cxx, std::string sources, std::string output, std::string cxxflags, std::string ldflags, std::string &return_text) {
    std::string total_return = "";
    std::ostringstream stream;
    stream << cxx << " " << cxxflags << " " << sources << " -o " << output << " " << ldflags << "\n";
    FILE *fptr = popen(stream.str().c_str(), "r");
    if(!fptr) {
        std::cerr << "Error opening " << cxx << "\n";
        exit(0);
    }
    char path[PATH_MAX];
    
    while(fgets(path, PATH_MAX, fptr) != NULL) {
        std::cout << path;
        total_return += std::string(path) + "\n";
    }
    int status = pclose(fptr);
    
    if(status == 0) {
        std::cout << "Succesfull compilation\n";
        return_text = total_return;
        return true;
    } else {
        std::cout << "Program errored..\n";
        return_text = total_return;
        return false;
    }
    
    return true;
}


int main(int argc, char **argv) {
    
    if(argc != 3) {
        std::cerr << "Requires two arguments: source files output_file\n";
        exit(0);
    }
    
    // so you would call this compile function
    // then if its succesfull or errors use the text returned for the output in the program
    // if your using this on windows you would want to replace "g++" with another cross compilers name like for Linux
    // Right now I am running this on  OS X and it compiles for OS X then using Mingw64 for Windows
    
    std::string return_value;
    /* using default compiler */
    if(compile("g++", argv[1], argv[2], "", "", return_value)) {
        std::cout << "Works..\n";
    } else {
        std::cout << "Doesn't work\n";
    }

    /* mingw64 */
    if(compile("x86_64-w64-mingw32-g++", argv[1], std::string(argv[2])+".exe", "", "-static-libgcc -static-libstdc++", return_value)) {
        std::cout << "Works..\n";
    } else {
        std::cout << "Doesn't work\n";
    }

    
    return 0;
}
