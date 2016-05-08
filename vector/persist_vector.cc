//
//  cxxVector
//
//  Created by Jared Bruni on 7/8/13.
//  Copyright (c) 2013 Jared Bruni. All rights reserved.
//

#include<iostream>
#include<vector>
#include<string>
#include<fstream>


template<typename T>
class PersistVector : public std::vector<T> {
public:
    PersistVector() = delete;
    explicit PersistVector(std::string filename) : filen{filename} {
        readData();
    }
    void readData() {
        file.open(filen, std::ios::in | std::ios::binary);
        
        if(!file.is_open()) {
            std::cout << "File could not be opened.\n";
            return;
        }
        std::cout << "Read.\n";
        while(!file.eof()) {
            T t;
            file.read((char*)&t, sizeof(t));
            if(file)
            this->push_back(t);
            
        }
        file.close();
        
    }
    void writeData() noexcept {
        file.open(filen, std::ios::out | std::ios::binary);
        if(!file.is_open()) {
            return;
        }
        for(auto it = this->begin(); it != this->end(); ++it) {
            T &t = *it;
            file.write((char*)&t, sizeof(t));
        }
        file.close();
    }
    
    ~PersistVector() {
        writeData();
    }
    
    void output(std::ostream &out) {
        out << "This is the vector = {\n";
        for(auto it = this->begin(); it != this->end(); ++it) {
            out << *it << "\n";
        }
        out << "\n}\n";
    }
    
protected:
    std::fstream file;
    std::string  filen;
};

// every time you run the program
// it will ask for input than each time it
// ends and starts over the list gets longer

int main(int argc, char **argv)
{
    PersistVector<std::string> p("test.txt");
    std::cout << "Enter input: ";
    std::string input;
    std::cin >> input;
    p.push_back(input);
    p.output(std::cout);
    return 0;
}

