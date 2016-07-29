/*
 written by Jared Bruni
 http://lostsidedead.com
 
*/

#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>

bool readFile(std::string fname, std::vector<std::string> &v);
bool writeFile(std::string fname, std::vector<std::string> &v);

int main(int argc, char **argv) {
    
    try {
        std::cout << "takes one argument, text file containing list to be sorted\n";
        std::vector<std::string> vec;
        if(argc != 2) {
            std::cerr << "Incorrect arguments.\n";
            return -1;
        } else {
            if(!readFile(argv[1], vec)) {
                std::cerr << "Error reading file.\n";
            }
            // loop through fec
            for(auto &i : vec) {
                std::cout << i << "\n";
            }
            
            std::sort(vec.begin(), vec.end());
            // another way to loop through after its sorted
            std::for_each(vec.begin(), vec.end(), [&](std::string n) {
                std::cout << "sorted: " << n << "\n";
            });
            
            writeFile(std::string(argv[1])+".sorted", vec);
            std::cout << "Wrote sorted to: " << std::string(argv[1])+".sorted" << "\n";
        }
        
    }
    catch(std::exception &e) {
        std::cerr << e.what() << "\n";
    }
    catch(...) {
        std::cerr << "Unknown error.\n";
    }
    
    return 0;
}



bool readFile(std::string fname, std::vector<std::string> &v) {
    std::fstream file;
    file.open(fname, std::ios::in);
    if(!file.is_open()) return false;
    
    while(!file.eof()) {
        std::string s;
        std::getline(file, s);
        if(file) v.push_back(s);
    }

    file.close();
    return true;
}

bool writeFile(std::string fname, std::vector<std::string> &v) {
    std::fstream file;
    file.open(fname, std::ios::out);
    if(!file.is_open()) return false;

    for(auto &i : v) {
        file << i << "\n";
    }
    file.close();
    return true;
    
    
}
