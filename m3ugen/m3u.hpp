#ifndef __M3U_GEN__H_
#define __M3U_GEN__H_

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<unistd.h>
#include<dirent.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<random>
#include<ctime>
#include<algorithm>

namespace m3u {
    
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
            
            lstat(fullpath.c_str(), &s);
            if(S_ISDIR(s.st_mode)) {
                if(f_info.length()>0 && f_info[0] != '.')
                    add_directory(path+"/"+f_info, files);

                continue;
            }
            if(f_info.length()>0 && f_info[0] != '.') {
                files.push_back(fullpath);
                std::cout << fullpath << "\n";
            }
        }
        closedir(dir);
    }
    
    bool isFileType(std::string fname, std::vector<std::string> &file_types) {
        for(unsigned int i = 0; i != file_types.size(); ++i) {
            if(fname.find(file_types[i]) != -1)
                return true;
            
        }
        return false;
    }
    
    bool gen_m3u_file(int sorted, std::string path, std::string filename, std::vector<std::string> &vec, std::vector<std::string> &file_types) {
        add_directory(path,  vec);
        std::fstream file;
        if(vec.size() == 0) return false;
        file.open(filename.c_str(), std::ios::out);
        if(!file.is_open()) {
            std::cerr << "Could not open output file.\n";
            return false;
        }
        
        if(sorted == 1) {
            std::sort(vec.begin(), vec.end());
        } else if(sorted == 2) {
            std::sort(vec.begin(), vec.end());
            std::default_random_engine dre(static_cast<int>(std::time(0)));
            std::shuffle(vec.begin(), vec.end(), dre);
        }
        
        unsigned int file_count = 0;
        for(unsigned int i = 0; i != vec.size(); ++i) {
            if(isFileType(vec[i],file_types)) {
                std::string fpath;
                fpath = vec[i];
                if(fpath[0] == '.' && fpath[1] == '/') {
                    fpath = fpath.substr(2,  fpath.length()-2);
                }
                
                file << fpath << "\n";
                std::cout << fpath << "\n";
                ++file_count;
            }
        }
        std::cout << "\n";
        file.close();
        std::cout << "Outputed " << file_count << " items.\n";
        return true;
    }
   
    
}

#endif
