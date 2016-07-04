#include<iostream>
#include<regex>
#include<dirent.h>
#include<sys/stat.h>
#include<fstream>


void add_directory(std::string _regex, std::string path, std::vector<std::string> &files) {
    DIR *dir = opendir(path.c_str());
    if(dir == NULL) {
        std::cerr << "Error could not open directory: " << path << "\n";
        return;
    }
    dirent *file_info;
    while( (file_info = readdir(dir)) != 0 ) {
        std::string f_info = file_info->d_name;
        if(f_info == "." || f_info == "..")  continue;
        std::string fullpath=path+"/"+f_info;
        struct stat s;
#ifdef WIN32
        stat(fullpath.c_str(), &s);
#else
        lstat(fullpath.c_str(), &s);
#endif
        if(S_ISDIR(s.st_mode)) {
            if(f_info.length()>0 && f_info[0] != '.')
                add_directory(_regex, path+"/"+f_info, files);
            
            continue;
        }
        if(f_info.length()>0 && f_info[0] != '.') {
            std::regex expression(_regex);
            if(std::regex_search(fullpath, expression)) {
                std::cout << fullpath << "\n";
                files.push_back(fullpath);
            }
        }
    }
    closedir(dir);
}

std::string output_Name(const std::string &filename) {
    auto pos = filename.rfind(".");
    std::string text = filename.substr(0, pos);
    text = text.substr(text.rfind("/")+1, text.length());
    return text;
}

void output_Makefile(std::vector<std::string> &files) {
    
    std::fstream file;
    file.open("Makefile.gen", std::ios::out);
    if(!file.is_open()) {
        std::cerr << "Error could not open Makefile.gen\n";
        exit(0);
    }
    
    
    file << "CFLAGS= -std=c++11\n";
    file << "all: \n";
    file << "\tmkdir -p build\n";
    
    for(unsigned int i = 0; i < files.size(); ++i) {
        file << "\t$(CXX) $(CFLAGS) ";
        file << files[i] << " -o " << "build/" << output_Name(files[i]) << "\n";
    }
    
    file.close();
}


int main(int argc, char **argv) {

    if(argc == 2) {
        std::vector<std::string> files;
    	add_directory(argv[1], ".", files);
        output_Makefile(files);
        
    }
    
    
    return 0;
}

