#include<dirent.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<iostream>
#include<string>

void printDir(std::string name) {
    DIR *dir = opendir(name.c_str());
    if(dir == NULL) {
        std::cerr << "Error could not open directory..\n";
        return;
    }
    dirent *file_info;
    while((file_info = readdir(dir)) != 0) {
        std::string f_info = file_info->d_name;
        if(f_info == "." || f_info == "..") continue;
        std::string fullpath=name+"/"+f_info;
        struct stat s;
        stat(fullpath.c_str(), &s);
        if(S_ISDIR(s.st_mode)) {
            if(f_info.length()>0 && f_info[0] != '.')
                printDir(name+"/"+f_info);
            continue;
        }
        if(f_info.length()>0 && f_info[0] != '.')
            std::cout << fullpath << "\n";
    }
    closedir(dir);
}


int main(int argc, char **argv) {
    if(argc != 2) {
        std::cerr << "Error requires one argument directory to print..\n";
        std::cerr << argv[0] << " directory\n";
        exit(EXIT_FAILURE);
    }
    
    printDir(argv[1]);
    return 0;
}
