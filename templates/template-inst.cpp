/* Explicit instantiation */

#include<iostream>
#include<string>

template<typename T>
void Echo(const T& type) {
    std::cout << type;
}

template<typename T>
class Value {
public:
    T val;
    void print() const { std::cout << val << "\n"; }
};


// Explicit instantiation
template void Echo<int>(const int &x);
template void Echo<std::string>(const std::string &x);
template class Value<int>;

int main() {
    Echo<std::string>("Hello world: ");
    Echo<int>(100);
    
    Value<int> v;
    v.val = 100;
    Echo<std::string>(" Value: ");
    v.print();
    return 0;
}