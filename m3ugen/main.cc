#include"m3u.hpp"
#include<iostream>


int main(int argc, char **argv) {
    
    if(argc != 4) {
        std::cout << "m3ugen directory output.m3u -s [sorted] or -r [shuffled] -n [as listed]\n";
        return 0;
    }
    
    
    
    std::string dir_path = argv[1];
    std::string output_name = argv[2];
    std::vector<std::string> file_list;
    std::vector<std::string> file_types;
    
    file_types.push_back("mp3");
    file_types.push_back("flac");
    file_types.push_back("ogg");
    file_types.push_back("wav");
    int sorted = 0;
    if(std::string(argv[3]) == "-s") sorted = 1;
    if(std::string(argv[3]) == "-r") sorted = 2;
    
    if(m3u::gen_m3u_file(sorted, dir_path, output_name, file_list, file_types)) {
        std::cout << "Generated: " << output_name << "\n";
    }
    
    
    return 0;
}