#include<iostream>
#include<vector>
#include<unistd.h>
#include<dirent.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<chrono>

class FileDB {
public:
    FileDB() = default;
    FileDB(const std::string &s) {
        std::cout << "Adding Files.\n";
        addFiles(s);
    }
    FileDB(const FileDB &fdb) {
        files = fdb.files;
    }
    
    FileDB(FileDB &&fdb) {
        files = std::move(fdb.files);
    }
    
    FileDB &operator=(const FileDB &fdb) {
        files = fdb.files;
        return *this;
    }
    
    FileDB &operator=(FileDB &&fdb) {
        files = std::move(fdb.files);
        return *this;
    }

protected:
    std::vector<std::string> files;
    
    
    void addFiles(const std::string &path) {
        DIR *dir = opendir(path.c_str());
        
        if(dir == 0) {
            std::cerr << "Error invalid path..\n";
            exit(-1);
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
                    addFiles(path+"/"+f_info);
                
                continue;
            }
            if(f_info.length()>0 && f_info[0] != '.') {
                files.push_back(fullpath);
                std::cout << fullpath << "\n";
            }
        }
        closedir(dir);
        
    }
};


int main(int argc, char **argv) {
    
    try{
        if(argc != 2) {
            std::cerr << "Must pass path of files to fill vector..\n";
            exit(0);
        }
        
        FileDB db(argv[1]);
        FileDB value;
        
        auto n1 = std::chrono::high_resolution_clock::now();
        
        value = std::move(db);
        
        auto n2 = std::chrono::high_resolution_clock::now();
        
        std::cout << "Move operation took " << std::chrono::duration_cast<std::chrono::nanoseconds>(n2-n1).count() << " nanoseconds.\n";
        
        auto n3 = std::chrono::high_resolution_clock::now();

        value = db;
        
        auto n4 = std::chrono::high_resolution_clock::now();
        
        std::cout << "Copy operation took: " << std::chrono::duration_cast<std::chrono::nanoseconds>(n4-n3).count() << " nanoseconds.\n";
        
    }
    catch(...) {
        std::cerr << "Error occoured quiting\n";
    }
    
    
    return 0;
}