/*
 Note: Requires you have unrar in your path. Download from http://rarlab.com
 written by Jared Bruni 2015
*/

#include<iostream>
#include<string>
#include<vector>
#include<dirent.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sstream>
#include<cstdio>
#include<cstdlib>
#include<unistd.h>


void add_directory(std::string path, std::vector<std::string> &files) {
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
                add_directory(path+"/"+f_info, files);
            
            continue;
        }
        if(f_info.length()>0 && f_info[0] != '.') {
            int part1_find = fullpath.find("1.rar");
            int rar = fullpath.find(".rar");
            int prar = fullpath.find("part");
            
            if(part1_find != -1 && prar != -1) {
                files.push_back(fullpath);
                std::cout << "added: " << fullpath << "\n";
            }
            
            if(rar != -1 && prar == -1) {
                files.push_back(fullpath);
                std::cout << "added: " << fullpath << "\n";
            }
        }
    }
    closedir(dir);
}

void extract_paths(std::string output_path, std::vector<std::string> &files) {
    
    for(unsigned int i = 0; i < files.size(); ++i) {
        std::ostringstream stream;
        stream << "unrar e -o+ \"" << files[i] << "\" \"" << output_path << "\"";
        FILE *fptr = popen(stream.str().c_str(), "r");
        if(!fptr) {
            std::cerr << "Error opening file: " << files[i] << "\n";
            continue;
        }
        
        char return_data[PATH_MAX];
        while(fgets(return_data, PATH_MAX, fptr) != NULL) {
            std::cout << return_data;
        }
        
        int status = pclose(fptr);
        if(status == 0) {
            std::cout << "Successfully extracted to output directory: " << output_path << "\n";
        } else {
            std::cout << "Extraction failed..\n";
        }
    }
}

int main(int argc, char **argv) {
    
    if(argc == 3) {
        std::vector<std::string> file_vec;
        add_directory(argv[1], file_vec);
        
        if(file_vec.size()>0) {
            extract_paths(argv[2], file_vec);
        }
        
    }
    else {
        std::cerr << "Program takes 2 arguments.\nunrar_extract source_dir full_output_path\n";
        exit(0);
    }
    
    return 0;
}