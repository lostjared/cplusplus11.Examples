/* 
 
    Source File can access text by line / col.
    written to be generic
 
 */

#include<iostream>
#include<string>
#include<vector>
#include<fstream>

template<typename T = std::basic_string<char>, typename Stream =  std::basic_fstream<char,  std::char_traits<char>>>
class SourceFile {
public:
    SourceFile();
    SourceFile(SourceFile<T> &t);
    SourceFile<T> &operator=(const SourceFile<T> &t);
    SourceFile(SourceFile<T> &&t);
    SourceFile<T> &operator=(const SourceFile<T> &&t);
    
    bool readFile(const T &path);
    T &operator[](unsigned int line);
    const int size() const { return code.size(); }
private:
    std::vector<T> code;
    
};

template<typename T, typename Stream>
SourceFile<T,Stream>::SourceFile() {
}

template<typename T, typename Stream>
SourceFile<T,Stream>::SourceFile(SourceFile<T> &t) {
    code = t.code;
}
template<typename T, typename Stream>
SourceFile<T> &SourceFile<T,Stream>::operator=(const SourceFile<T> &t) {
    if (this == &t) {
        return *this;
    }
    code = t.code;
    return *this;
}
template<typename T, typename Stream>
SourceFile<T,Stream>::SourceFile(SourceFile<T> &&t) {
    code = std::move(t);
}
template<typename T, typename Stream>
SourceFile<T> &SourceFile<T,Stream>::operator=(const SourceFile<T> &&t) {
    code = std::move(t.code);
    return *this;
}

template<typename T, typename Stream>
bool SourceFile<T,Stream>::readFile(const T &path) {
    Stream file;
    file.open(path, std::ios::in);
    if(!file.is_open()) return false;
    while(!file.eof()) {
        T s;
        std::getline(file, s);
        if(file) code.push_back(s);
    }
    file.close();
    return true;
}

template<typename T, typename Stream>
T &SourceFile<T,Stream>::operator[](unsigned int line) {
    if(line >= 0 && line < code.size()) return code[line];
    throw std::out_of_range("wrong index");
}

int main(int argc, char **argv) {
    
    if(argc != 2) {
        std::cout << "Error requires one argument..\n";
        return 0;
    }
    
    SourceFile<std::string> source;
    
    if(source.readFile(argv[1])) {
        std::cout <<  "File opened and read...: " << source.size() << "\n";
        for(unsigned int i = 0; i < source.size(); ++i) {
            std::cout << i << ": " << source[i] << "\n";
        }
        
    } else {
        std::cout << "Could not read file..\n";
    }
    return 0;
}

