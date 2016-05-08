#include<iostream>
#include<string>
#include<vector>
#include<fstream>

bool containsData(const std::string &text) {
    for(auto &i : text) {
        if(i != ' ' && i != '\n' && i != '\r' && i != '\t') return true;
    }
    return false;
}

int main(int argc, char **argv) {
    
    if(argc != 2) {
        std::cerr << "Requires one argument the txt file.\n";
        return 0;
    }
    
    std::fstream file;
    file.open(argv[1], std::ios::in);
    if(!file.is_open()) {
        std::cerr << "Error opening file: "<<argv[0] << "\n";
        return 0;
    }
    
    std::fstream ofile;
    std::string ofile_n;

    ofile_n=argv[1];
    ofile_n+=".txt";
    
    ofile.open(ofile_n, std::ios::out);
    if(!ofile.is_open()) {
        std::cerr << "Error could not open file: " << ofile_n << "\n";
        return 0;
    }
    while(!file.eof()) {
        std::string n;
        std::getline(file, n);
        if(n.length()>0 && containsData(n)) {
            ofile << n << "\n";
        }
    }
    
    ofile.close();
    file.close();
    std::cout << "Outputed: " << ofile_n << "\n";
    return 0;
}