
/*
 written by Jared Bruni
 http://lostsidedead.com
*/

#include<iostream>
#include<vector>
#include<fstream>

template<typename T, typename Iter>
T addup(Iter start, Iter stop) {
    T total{};
    for(Iter i = start; i != stop; ++i)
        total += *i;
    
    return total;
}

template<typename Iter>
bool WriteVector(Iter start, Iter stop, std::string filename) {
    std::fstream file;
    file.open(filename, std::ios::out);
    if(!file.is_open()) return false;
    for(Iter i = start; i != stop; ++i) {
        file << *i << "\n";
    }
    file.close();
    return true;
}

int main(int argc, char **argv) {
    std::cout << "Enter 4 values: ";
    std::vector<float> varr;
    
    for(unsigned int z = 0; z < 4; ++z) {
        float f;
        std::cin >> f;
        varr.push_back(f);
    }
    
    float value=addup<float, std::vector<float>::iterator>(varr.begin(), varr.end());
    value /= varr.size();
    
    std::cout << " Average is: " << value << "\n";
    
    for(auto i = varr.begin(); i != varr.end(); ++i)
        std::cout << "Value is: " << *i << "\n";
    
    if(WriteVector(varr.begin(), varr.end(), "file.txt")) {
        std::cout << "Successfully wrote vector to file.txt\n";
    }
    else {
        std::cout << "Could not write to file.txt.\n";
    }
    return 0;
}