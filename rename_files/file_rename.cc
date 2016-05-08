/*
 written by Jared Bruni
 http://lostsidedead.com
*/

/*

 This tool will bulk rename files with a common prefix
 to use:
 
 ./rename-file /path/to/directory /path/to/directory/temp/prefix
 
 will copy all files in directory to /path/to/directory/temp each file
 name prefix_000001 and its file extension. So for a cc file it would
 prefix_00001.cc prefix_00002.cc etc
 
 The output directory has to exisit.
 
*/

#include<iostream>
#include<string>
#include<vector>
#include<unistd.h>
#include<dirent.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fstream>
#include<sstream>
#include<iomanip>


std::vector<std::string> files;

bool copy_file(std::string source, std::string dest) {
    std::fstream file_src, file_dest;
    file_src.open(source, std::ios::in | std::ios::binary);
    if(!file_src.is_open()) {
        std::cerr << " could not open file: " << source << "\n";
        return true;
    }
    file_dest.open(dest, std::ios::out | std::ios::binary);
    if(!file_dest.is_open()) {
        std::cerr << " error could not open file: " << dest << "\n";
        file_src.close();
        return false;
    }
    file_src.seekg(0, std::ios::end);
    size_t length = file_src.tellg();
    file_src.seekg(0, std::ios::beg);
    
    char *buffer = new char [ length + 1 ];
    file_src.read((char*)buffer, length);
    file_dest.write((char*)buffer, length);
    delete [] buffer;
    file_src.close();
    file_dest.close();
    return true;
}

void add_directory(std::string path) {
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
            add_directory(path+"/"+f_info);
            continue;
        }
        if(f_info.length()>0 && f_info[0] != '.')
        files.push_back(fullpath);
    }
    closedir(dir);
}

void moveFiles(std::string path_prefix) {
    for(unsigned int i = 0; i < files.size(); ++i) {
        std::ostringstream stream;
        std::string fname, ext;
        int pos = files[i].rfind(".");
        int pos2 = files[i].rfind("/");
        int pos3 = 0;
        if(pos == 0) {
            fname = files[i];
            ext = "";
        } else if(pos > pos2) {
            if(pos2 >= 0) {
                pos3 = pos2+1;
            } else pos3 = 0;
            fname = files[i].substr(pos3, pos-pos2-1);
            ext = files[i].substr(pos, files[i].length()-pos);
        } else {
            fname = files[i].substr(pos2+1, files[i].length());
            ext = "";
        }
        stream << path_prefix << "_" << std::setfill('0') << std::setw(6) << i << ext;
        std::cout << "attempting to copy " << std::setw(30) << files[i] << " to " << std::setw(30) << stream.str() << "\n";
        if(copy_file(files[i], stream.str()) == true) {
            std::cout << ".... copied\n";
        }
    }
}

int main(int argc, char **argv) {
    std::cout << "Bulk file rename\n";
    if(argc != 3) {
        std::cout << "Invalid arguments.\n";
        std::cout << "rename-file directory /path/prefix/filename\n";
        return 0;
    }
    std::string location_path_prefix=argv[2];
    std::string dir_name = argv[1];
    if(dir_name.size()>2 && dir_name[0] == '.' && dir_name[1] != '.') {
        char buf[1024];
        getcwd(buf, 1024);
        dir_name = buf;
    }
    add_directory(dir_name);
    if(files.size()>0)
        moveFiles(location_path_prefix);

    return 0;
}