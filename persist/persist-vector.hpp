/*
 
 Example C++ Persist Vector Template
 written by Jared Bruni
 
 in public domain
 
*/



#ifndef __PERSIST_VECTOR__H__
#define __PERSIST_VECTOR__H__

#include<iostream>
#include<string>
#include<vector>
#include<cstdlib>
#include<fstream>

namespace persist {
    
    
    // Default Read/Write function objects work with POD types
    template<typename T>
    class DefaultRead {
    public:
        void operator()(T &type, std::fstream &file) {
            file.read(reinterpret_cast<char*>(&type), sizeof(T));
            
        }
    };
    
    template<typename T>
    class DefaultWrite {
    public:
        void operator()(T &type, std::fstream &file) {
            file.write(reinterpret_cast<char*>(&type), sizeof(T));
        }
    };
    
    
    // class template for persist vector
    template<typename T, typename Read = DefaultRead<T>, typename Write = DefaultWrite<T>>
    class Vector {
    public:
        // constructor initalize
        Vector(std::string file_name, size_t res) : file_n(file_name) {
            // read
            vec.reserve(res);
            readFile(file_name);
        }
        
        ~Vector() {
            writeFile(file_n);
        }
        
        // connstructors
        Vector(const Vector<T,Read,Write> &cv) : vec(cv.vec), file_n(cv.file_n) {
            
        }
        
        Vector(const Vector<T,Read,Write> &&cv) : vec(std::move(cv.vec)), file_n(cv.file_n) {
            
        }
        
        // overloaded = operators
        Vector<T,Read,Write> &operator=(const Vector<T,Read,Write> &cv) {
            vec = cv.vec;
            file_n = cv.file_n;
        }
        
        Vector<T,Read,Write> &operator=(const Vector<T,Read,Write> &&cv) {
            vec = std::move(cv.vec);
            file_n = cv.file_n;
        }
        
        // read vector from file
        void readFile(std::string filename) {
            std::fstream file;
            file.open(filename, std::ios::in | std::ios::binary);
            if(!file.is_open()) {
                std::cerr << "Error opening file: " << filename << "\n";
                return;
            }
            while(file && !file.eof()) {
                T type;
                read_f(type, file);
                if(file) vec.push_back(type);
            }
            file.close();
        }
        // write vector to file
        void writeFile(std::string filename) {
            std::fstream file;
            file.open(filename, std::ios::out | std::ios::binary);
            if(!file.is_open()) {
                std::cerr << "Error opening file: " << filename << "\n";
                return;
            }
            for(auto i = vec.begin(), end = vec.end(); i != end; ++i) {
                write_f(*i,file);
            }
            file.close();
        }
        
        T &operator[](size_t pos) {
            return vec[pos];
        }
        
        // use -> operator to access the vector
        inline std::vector<T> *operator->() { return &vec; }
        // use 'getvector' to get reference to vector
        inline std::vector<T> &operator*() { return vec; }
    protected:
        std::vector<T> vec;
        std::string file_n;
    private:
        Read read_f; // read function object
        Write write_f; // write function object
    };
    
}










#endif
