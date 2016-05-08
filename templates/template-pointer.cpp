#include<iostream>
#include<fstream>
#include<string>
#include<cstdio>
#include<cstdlib>


template<typename T>
class LongPointer {
public:
    LongPointer(T *v) : ptr((unsigned long)v) {}
    unsigned long &intValue() {
        return ptr;
    }
    T *ptrValue() { return (T*)ptr; }
private:
    unsigned long ptr;
    
};

int main() {
    
    
    char *value = (char*) std::calloc(1, 100);
    sprintf(value, "%s", "Hello World");
    LongPointer<char> ptr(value);
    
    std::cout << "Integer value for Pointer: " << ptr.intValue() << "\n";
    std::cout << "String value char* ptr: " << (char*)ptr.ptrValue() << "\n";
    
    free(value);
    
    return 0;
}
