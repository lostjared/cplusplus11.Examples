#include<dirent.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<iostream>
#include<string>
#include<regex>

void printDir(std::string name, std::regex &x) {
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
                printDir(name+"/"+f_info, x);
            continue;
        }
        if(f_info.length()>0 && f_info[0] != '.')
            if(std::regex_search(fullpath, x) == true)
                std::cout << fullpath << "\n";
    }
    closedir(dir);
}


int main(int argc, char **argv) {
    if(argc != 3) {
        std::cerr << "Error requires two arguments you gave: " << argc << " required directory to search and regular expression\n";
        std::cerr << argv[0] << " dir \"regex\"\n";
        exit(EXIT_FAILURE);
    }
    try {
        std::regex x(argv[2], std::regex::grep);
    	printDir(argv[1], x);
    } catch(std::regex_error &e) {
        std::cout << e.what() << "\n";
    } catch(std::exception &e) {
        std::cout << e.what() << "\n";
    }
    return 0;
}


