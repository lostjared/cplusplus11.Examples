/* Example of specialization */


#include<iostream>
#include<string>

template<typename T>
class Value {
public:
    T temp;
    void print() const;
};

template<typename T>
void Value<T>::print() const {
    std::cout << std::dec << temp << "\n";
}

template<>
class Value<void *> {
public:
    void *temp;
    void print() const;
};

void Value<void *>::print() const {
    std::cout << "0x" << std::hex << (unsigned long)temp << "\n";
}


template<typename T>
void Print(Value<T> &type) {
    std::cout << "Value<T>: ";
    type.print();
}

template<>
void Print(Value<void*> &v) {
    std::cout << "Value<void *>: ";
    v.print();
}



int main() {

    Value<int> v; // T is int
    v.temp = 100;
    v.print(); // print out integer
    
    Value<void *> v2; // specialization
    v2.temp = &v;
    v2.print(); // print out pointer
    
    Print(v); // print out Value<int>
    Print(v2); // print out Value<void *>
    
    return 0;
}