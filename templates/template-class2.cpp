/*
 Easier way to do the SourceFile class template
 requires only 1 template argument to work 
*/




#include<iostream>
#include<string>
#include<fstream>
#include<vector>


template<typename T = char, typename String = std::basic_string<T>, typename Stream = std::basic_fstream<T, std::char_traits<T>>>
class SourceFile {
public:
    SourceFile() = default;
    
    SourceFile(const SourceFile<T> &t) {
        code = t.code;
    }
    
    SourceFile(const SourceFile<T> &&t) {
        code = std::move(t.code);
    }
    
    SourceFile<T> &operator=(const SourceFile<T> &t) {
        if(this == &t) { return *this; }
        code = t.code;
        return *this;
    }
    
    SourceFile<T> &operator=(const SourceFile<T> &&t) {
        code = std::move(t.code);
        return *this;
    }
    
    bool readFile(const String &source_file) {
        Stream file;
        file.open(source_file, std::ios::in);
        if(!file.is_open()) return false;
        while(!file.eof()) {
            String s;
            std::getline(file, s);
            if(file) code.push_back(s);
        }
        return true;
    }
    
    String &operator[](unsigned int pos) {
        if(pos >= 0 && pos < code.size()) return code[pos];
        throw std::out_of_range("Out of range for SourceFile::operator[]");
    }
    
    const int size() const { return code.size(); }
    
private:
    std::vector<String> code;
};


int main(int argc, char **argv) {
    
    if(argc != 2) {
        std::cerr << "Error requires one argument..\n";
        return 0;
    }
    
    SourceFile<char> source_code;
    if(source_code.readFile(argv[1])) {
        
        for(unsigned int i = 0; i < source_code.size(); ++i) {
            std::cout << i << ": " << source_code[i] << "\n";
        }
        
    } else {
        std::cout << "Error could not open file..\n";
    }
    
    return 0;
}